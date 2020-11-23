#ifndef SM2COOP_HEADER_H
#define SM2COOP_HEADER_H

#include <stddef.h>
#include <openssl/opensslconf.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/objects.h>
#include <string.h>

#ifndef OPENSSL_NO_SM2COOP

# ifdef __cplusplus
extern "C"
{
# endif // __cplusplus


    /**
     * \brief           The SM2 Cooperative context structure, holds key to operate on
     * \note            The server side and client side have the same key structure
     * \note            Please turn to ec.h and ossl_typ.h for value I/O
     */
    struct sm2coop_ctx {
        EC_GROUP *grp;     /*!<  SHARED:  Elliptic curve and base point             */
        BIGNUM *hd;        /*!<  PRIVATE: The secret value                          */
        EC_POINT *W;       /*!<  PUBLIC:  The public key for signing                */
        EC_POINT *P;       /*!<  PUBLIC:  The public key for signature verification */
    };
    
    typedef struct sm2coop_ctx SM2COOP;
     
     /**
      * \return   return newly created EC_GROUP object(the curve is sm2)
      * \note     the user usually do not use this function
      **/
     EC_GROUP *sm2coop_load_default_curve(void);
    
    /**
     * \brief           This function initializes the SM2Coop context
     *
     * \return          the inited sm2coop_ctx
     *
     */
    SM2COOP* SM2COOP_new(void);

    /**
     * \brief          This function copies the components of an SM2Coop context.
     *
     * \param dst      The destination context. This must be initialized.
     *
     * \param src      The source context. This must be initialized.
     *
     * \return         0 on success, otherwise failure
     *
     */
    int SM2COOP_copy(SM2COOP* dst, const SM2COOP* src);

    /**
     * \brief          This function frees the SM2Coop context.
     *
     * \param ctx      The context to free. May be NULL, in which case
     *                 this function is a no-op. If it is not NULL, it must
     *                 point to an initialized context.
     */
    void SM2COOP_free(SM2COOP* ctx);

    /**
     * \brief          This function implements keygen between client and server, ensure
     *                 that the two parties hold the same key P
     *
     * \param client      The client context. This must be initialized
     *
     * \param server      The server context. This must be initialized.
     *
     * \return         0 on success, otherwise failure
     *
     */
    int SM2COOP_keygen(SM2COOP* client, SM2COOP* server);


    /**
     * \brief           The SM2Coop Key Generation Protocol Session Context
     *
     * \note            The server side and client side have the same structure
     *
     * \note            Please turn to ec.h and ossl_typ.h for value I/O
     */
    struct sm2coop_keygen_session{
        SM2COOP *key; // the key to be created, get the key here after finishing the protocol
    };

    typedef struct sm2coop_keygen_session SM2COOP_KEYGEN;

    /**
     * \brief           This function initializes the keygen session
     *
     * \param ctx       Context to initialize, Could NOT be NULL
     *
     * \note            This function will set the grp SM2COOP
     *
     */
    SM2COOP_KEYGEN* SM2COOP_KEYGEN_new(void);

    /**
     * \brief          This function copies the components of the keygen session.
     *
     * \param dst      The destination session. This must be initialized.
     *
     * \param src      The source session. This must be initialized.
     *
     * \return          0 on success, otherwise fail
     */
    int SM2COOP_KEYGEN_copy(SM2COOP_KEYGEN* dst, const SM2COOP_KEYGEN* src);

    /**
     * \brief          This function frees the the keygen session.
     *
     * \param ctx      The session to free. May be NULL, in which case
     *                 this function is a no-op. If it is not NULL, it must
     *                 point to an initialized session.
     */
    void SM2COOP_KEYGEN_free(SM2COOP_KEYGEN* ctx);


    /**
     * \brief           start the key generation protocol, let the client send key to server
     *
     * \param ctx       the keygen session, MUST BE INITIALIZED & HAVE ITS KEY'S GRP SET
     *
     * \param max_client_w_len the size limit of the buffer
     * 
     * \param client_w  the buffer to put the W to send to server, MUST NOT BE NULL
     *
     * \param client_w_len out param, tells the used size of client_w, MUST NOT BE NULL
     *
     * \return          0 if success, otherwise fail
     *
     * \note            the keygen session should be considered invalid after failure, and should be freed immediately
     *
     */
     int SM2COOP_KEYGEN_client_send_key(
        SM2COOP_KEYGEN* keygen,
        unsigned char* client_w, size_t max_client_w_len, size_t* client_w_len
     );

    /**
     * \brief           continue the key generation protocol,let the server receive client's key and respond with server's key
     *					    THE PROTOCOL FOR SERVER COMPLETES AFTER THIS FUNCTION
     *
     * \param ctx       the keygen session, MUST BE INITIALIZED & HAVE ITS KEY'S GRP SET
     *
     * \param client_w  the buffer to read the W from client, MUST NOT BE NULL
     *
     * \param client_w_len the length of client_w
     *
     * \param server_w  the buffer to put the W to send to client, MUST NOT BE NULL
     *
     * \param max_server_w_len the size limit of the buffer
     * 
     * \param server_w_len out param, tells the used size of server_w. MUST NOT BE NULL
     *
     * \return          0 if success, otherwise fail
     *
     */
    int SM2COOP_KEYGEN_server_exchange_key(
        SM2COOP_KEYGEN* keygen,
        const unsigned char* client_w, size_t client_w_len,
        unsigned char* server_w, size_t max_server_w_len, size_t* server_w_len
    );

    /**
     * \brief           complete the key generation protocol,let the client receive server's key
     *					    THE PROTOCOL FOR CLIENT COMPLETES AFTER THIS FUNCTION
     *
     * \param ctx       the keygen session context, MUST NOT BE NULL, INITIALIZED, AND RAN client_send_key
     *
     * \param server_w  the w from server, MUST NOT BE NULL
     *
     * \param server_w_len the length of w
     *
     * \return          0 if success, otherwise fail
     *
     * \note            the keygen session context should be considered invalid after failure, and should be freed immediately
     *
     */
    int SM2COOP_KEYGEN_client_receive_key(
        SM2COOP_KEYGEN* keygen,
        const unsigned char* server_w, size_t server_w_len
    );



    /**
     * \brief           run sm2coop encryption algorithm, result is ASN.1 DER encoded
     *
     * \param ctx       the sm2coop context, must have at least P and grp loaded
     *
     * \param buffer    data to encrypt, MUST NOT BE NULL
     *
     * \param blen      data length
     *
     * \param out       buffer for ciphertext, MUST NOT BE NULL
     *
     * \param max_olen  buffer length limit for ciphertext
     * 
     * \param olen      pointer to return the ciphertext length, MUST NOT BE NULL
     *
     * \return          0 if successful, otherwise error
     *
     * \note            this is essentially same as SM2 encryption algorithm
     *
     * \note            according to GM/T 2009-2012, the ASN.1 of ciphertext is:
     *                  SM2Cipher ::= SEQENCE(
     *						XCoordinate INTEGER,
     *						YCoordinate INTEGER,
     * 						HASH        OCTET STRING SIZE(32),
     *						CipherText  OCTET STRING
     *					)
     *
     */
    int SM2COOP_encrypt(
        SM2COOP* sm2coop_ctx,
        const unsigned char* buffer, size_t blen,
        unsigned char* out, size_t max_olen, size_t* olen
    );



    /**
     * \brief           The SM2Coop Decrypt protocol client session state
     *					    offsets into the ciphertext to extract data without resolving ASN.1 again
     */
    struct sm2coop_decrypt_client{
        EC_GROUP* group;
        EC_POINT *C1;       
        unsigned char *C2;
        int C2_len;
        unsigned char *C3;
    };

    typedef struct sm2coop_decrypt_client SM2COOP_DEC_CLNT;

    /**
     * \brief           This function initializes the decrypt context
     *
     * \param ctx       Context to initialize, MUST NOT be NULL
     *
     */
    SM2COOP_DEC_CLNT* SM2COOP_DEC_CLNT_new(void);

    /**
     * \brief          This function copies the components of the decrypt session.
     *
     * \param dst      The destination session. This must be initialized.
     * \param src      The source session. This must be initialized.
     *
     * \return          0 if successful, otherwise failure
     */
    int SM2COOP_DEC_CLNT_copy(SM2COOP_DEC_CLNT* dst, const SM2COOP_DEC_CLNT* src);

    /**
     * \brief          This function frees the the decrypt session.
     *
     * \param ctx      The session to free. May be \c NULL, in which case
     *                 this function is a no-op. If it is not \c NULL, it must
     *                 point to an initialized session.
     */
    void SM2COOP_DEC_CLNT_free(SM2COOP_DEC_CLNT* ctx);

    /**
     * \brief           starts the sm2 decrypt protocol, the ciphertext is assumed to be ASN.1 DER encoded
     *						see the corresponding encrypt function for encoding details
     *
     * \param ctx       the sm2coop context, must have at least hd, P and grp loaded
     *
     * \param decrypt_ctx the extra session for decryption
     *
     * \param ctext     the ciphertext
     *
     * \param clen      the ciphertext byte length
     *
     * \param out       the request to send buffer
     *
     * \param max_olen  max capacity of the request buffer
     * 
     * \param olen      pointer for returning request length
     *
     * \return          0 if successful, otherwise failure
     *
     * \note            the decrypt session context should be considered invalid after failure, and should be freed immediately
     *
     */
    int SM2COOP_DEC_client_start(
        SM2COOP* key,
        SM2COOP_DEC_CLNT* decrypt_ctx,
        const unsigned char* ctext, size_t clen,
        unsigned char* out, size_t max_olen, size_t* olen
    );

    /**
     * \brief           continue the decrypt protocol,let the server respond to request
     *					    THE PROTOCOL FOR SERVER COMPLETES AFTER THIS FUNCTION
     *
     * \param ctx       the sm2coop context, must have at least hd and grp loaded
     *
     * \param req       the buffer to put the request from client, MUST NOT BE NULL
     *
     * \param req_len   the length of request
     *
     * \param resp      the buffer to put response of server, MUST NOT BE NULL
     *
     * \param max_resplen the size limit of the response buffer
     * 
     * \param resplen out param, tells the actual size of response, MUST NOT BE NULL
     *
     * \return          0 if successful, otherwise failure
     *
     */
    int SM2COOP_DEC_server_respond(
        SM2COOP* key,
        const unsigned char* req, size_t req_len,
        unsigned char* resp, size_t max_resplen, size_t* resplen
    );


    /**
     * \brief           completes the sm2 decrypt protocol, the ciphertext is assumed to be ASN.1 DER encoded
     *						see the corresponding encrypt function for encoding details
     *						THE PROTOCOL FOR CLIENT COMPLETES AFTER THIS FUNCTION
     *
     * \param ctx       the sm2coop context, must have grp and hd loaded
     *
     * \param decrypt_ctx the extra context for decryption, MUST NOT BE NULL AND RAN client_start
     *
     * \param resp       the response, MUST NOT BE NULL
     *
     * \param resp_len   the response's length
     *
     * \param out        the plaintext buffer, MUST NOT BE NULL
     *
     * \param max_olen   max capacity of the plaintext buffer
     * 
     * \param olen       pointer for returning plaintext length, MUST NOT BE NULL
     *
     * \return           0 if successful, otherwise failure
     *
     * \note            the decrypt session context should be considered invalid after failure, and should be freed immediately
     *
     */
    int SM2COOP_DEC_client_complete(
        SM2COOP* key,
        SM2COOP_DEC_CLNT* decrypt_ctx,
        const unsigned char* resp, size_t resp_len,
        unsigned char* out, size_t max_olen, size_t* olen
    );



    /**
     * \brief           The SM2Coop signature client session
     */
    struct sm2coop_sign_client{
        BIGNUM *k;
    };

    typedef struct sm2coop_sign_client SM2COOP_SIGN_CLNT;

    /**
     * \brief           This function initializes the signature session
     *
     * \param ctx       to initialize, MUST NOT be NULL
     *
     */
    SM2COOP_SIGN_CLNT* SM2COOP_SIGN_CLNT_new(void);

    /**
     * \brief          This function copies the components of the signature session.
     *
     * \param dst      The destination session. This must be initialized.
     * \param src      The source session. This must be initialized.
     *
     * \return          0 if successful, otherwise failure
     */
    int SM2COOP_SIGN_CLNT_copy(SM2COOP_SIGN_CLNT* dst, const SM2COOP_SIGN_CLNT* src);

    /**
     * \brief          This function frees the the signature session.
     *
     * \param ctx      The session to free. May be \c NULL, in which case
     *                 this function is a no-op. If it is not \c NULL, it must
     *                 point to an initialized session.
     */
    void SM2COOP_SIGN_CLNT_free(SM2COOP_SIGN_CLNT* ctx);

    /**
     * \brief           start the sm2coop signature algorithm, the result is encoded in ASN.1 DER
     *
     * \param ctx       the sm2coop context, must have hd, W, P, grp present
     *
     * \param sign_ctx  the sm2coop signature client session
     *
     * \param msg         the message to sign
     *
     * \param msglen      the length of message
     *
     * \param dgst      output buffer for the digest of message to sign
     *
     * \param max_dgstlen  max buffer capacity of digest buffer
     *
     * \param dgstlen   out param to collect the actual length of digest
     *
     * \param req      output buffer for the request to send to server
     *
     * \param max_reqlen  max buffer capacity of request buffer
     *
     * \param reqlen   out param to collect the actual length of request
     *
     * \return          0 if successful, otherwise failure
     *
     * \note            the encoding of signature in ASN.1 is:
     *                  SM2 Signature::= (
     *						R INTEGER,
     *						S INTEGER
     *					)
     *					The length of R and S are 32Bytes, respectively
     *
     * \note           Such encoding is only guranteed when using the standard curve parameter
     *                     the length might be not 32Bytes if using other curve
     */
    int SM2COOP_SIGN_client_start(
        SM2COOP* key,
        SM2COOP_SIGN_CLNT* sign_ctx,
        const unsigned char* msg, size_t msglen,
        unsigned char* dgst, size_t max_dgstlen, size_t* dgstlen,
        unsigned char* req, size_t max_reqlen, size_t* reqlen
    );

    /**
     * \brief             run the sm2 signature algorithm with custom userID,
     *                        the result is encoded as ASN.1 DER
     *
     * \param ctx         the sm2coop context, must have hd, W, P, grp present
     *
     * \param sign_ctx    the signature session state
     *
     * \param id          user ID, just a byte string
     *
     * \param idlen       id string length
     *
     * \param msg         the message to sign
     *
     * \param msglen      the length of message
     *
     * \param dgst        digest output buffer
     *
     * \param max_dgstlen  max buffer capacity of digest buffer
     *
     * \param dgstlen      pointer for returned digest length
     *
     * \param req         request output buffer
     *
     * \param max_reqlen  max buffer capacity of request buffer
     *
     * \param reqlen      pointer for returned request length
     *
     * \return          0 if successful, otherwise failure
     *
     */
    int SM2COOP_SIGN_client_start_withID(
        SM2COOP* key,
        SM2COOP_SIGN_CLNT* sign_ctx,
        const unsigned char* id, size_t idlen,
        const unsigned char* msg, size_t msglen,
        unsigned char* dgst, size_t max_dgstlen, size_t* dgstlen,
        unsigned char* req, size_t max_reqlen, size_t* reqlen
    );

    /**
     * \brief             respond the request of the sm2 signature algorithm,
     *					    THE PROTOCOL FOR SERVER COMPLETES AFTER THIS FUNCTION
     *
     * \param ctx         the sm2coop context, must have hd, W, P, grp present
     *
     * \param dgst        digest input buffer
     *
     * \param dgst_len    size of digest
     *
     * \param req         request input buffer
     *
     * \param req_len     size of request
     *
     * \param resp        response output buffer
     *
     * \param max_resplen  max buffer capacity of response buffer
     *
     * \param resplen      pointer for returned response length
     *
     * \return          0 if successful, otherwise failure
     *
     */
    int SM2COOP_SIGN_server_respond(
        SM2COOP* key,
        const unsigned char* dgst, size_t dgst_len,
        const unsigned char* req, size_t req_len,
        unsigned char* resp, size_t max_resplen, size_t* resplen
    );

    /**
     * \brief             complete the sm2 signature algorithm,
     *					    THE PROTOCOL FOR CLIENT COMPLETES AFTER THIS FUNCTION
     *
     * \param ctx         the sm2coop context, must have hd, W, P, grp present
     *
     * \param sign_ctx    the signature session state
     *
     * \param resp         response input buffer
     *
     * \param resplen     size of response
     *
     * \param sig        signature output buffer
     *
     * \param max_siglen  max buffer capacity of signature buffer
     *
     * \param siglen      pointer for returned signature length
     *
     * \return          0 if successful, otherwise failure
     *
     */
    int SM2COOP_SIGN_client_complete(
        SM2COOP* key,
        SM2COOP_SIGN_CLNT* sign_ctx,
        const unsigned char* resp, size_t resplen,
        unsigned char* sig, size_t max_siglen, size_t* siglen
    );

    /**
     * \brief           verify the sm2coop signature,
     *                      the result is encoded in ASN.1
     *
     * \param ctx       the sm2coop context, must have P & grp present
     *
     * \param msg   the message to verify
     *
     * \param msglen    the message length
     *
     * \param sig       the signature to verify
     *
     * \param siglen    signature length
     *
     * \return          0 if successful, otherwise failure
     *
     * \note            this is essentially same as sm2 signature verify
     *
     */
    int SM2COOP_verify(
        SM2COOP* key,
        const unsigned char* msg, size_t msglen,
        const unsigned char* sig, size_t siglen
    );

    /**
     *
     * \brief           verify SM2Coop signature
     *
     * \param ctx       the sm2coop context, must have P & grp present
     *
     * \param id        user id such as user mail string
     *
     * \param idlen     id string length
     *
     * \param msg       message
     *
     * \param msglen    message string length
     *
     * \param sig       the signature of data
     *
     * \param siglen    signature array length
     *
     * \return          0 if successful, otherwise failed
     *
     * \note            this is essentially same as sm2 signature verify
     *
     */
    int SM2COOP_verify_withID(
        SM2COOP* key,
        const unsigned char* id, size_t idlen,
        const unsigned char* msg, size_t msglen,
        const unsigned char* sig, size_t siglen
    );

# ifdef __cplusplus
}
# endif // __cplusplus


#ifndef OPENSSL_NO_ERR
#ifdef __cplusplus
extern "C"
{
#endif

#include <openssl/err.h>
#define SM2COOPerr(f, r) ERR_PUT_error(ERR_LIB_SM2COOP, (f), (r), __FILE__, __LINE__)

int ERR_load_SM2COOP_strings(void);
/*
 * SM2COOP function codes.
 */
#define SM2COOP_F_CTX_NEW 120
#define SM2COOP_F_CTX_CPY 121
#define SM2COOP_F_CTX_KEYGEN 122

#define SM2COOP_F_KEY_NEW 125
#define SM2COOP_F_CLNT_SEND_KEY 126
#define SM2COOP_F_SERVR_EXCH_KEY 127
#define SM2COOP_F_CLNT_REC_KEY 128
#define SM2COOP_F_WRITE_X_Y 129
#define SM2COOP_F_READ_X_Y 130
#define SM2COOP_F_CPU_P 131

#define SM2COOP_F_ENC 135
#define SM2COOP_F_DEC_NEW 136
#define SM2COOP_F_DEC_CPY 137
#define SM2COOP_F_DEC_CLNT_STAT 138
#define SM2COOP_F_DEC_SERVR_RESP 139
#define SM2COOP_F_DEC_CLNT_CMPE 140

#define SM2COOP_F_CPU_HASHM 144
#define SM2COOP_F_SIGN_NEW 145
#define SM2COOP_F_SIGN_CPY 146
#define SM2COOP_F_SING_CLNT_STAT 147
#define SM2COOP_F_SING_SERVR_RESP 148
#define SM2COOP_F_SIGN_CLNT_CMPE 149
#define SM2COOP_VERIFY 150


/*
 * SM2COOP reason codes.
 */

#define SM2COOP_R_ALLOCATE_ERROR 120
#define SM2COOP_R_INITIALIZE_IS_NULL 121
#define SM2COOP_R_COPY_ERROR 122
#define SM2COOP_R_CALL_FUN_ERROR 123
#define SM2COOP_R_NULL_PARAMETER 124
#define SM2COOP_R_ASN_TRANSFORM_ERROR 125
#define SM2COOP_R_ASN_SET_ERROR 126
#define SM2COOP_R_ASN_GET_ERROR 127
#define SM2COOP_R_KDF_ERROR 128
#define SM2COOP_R_OUTPUT_LARG 129

#define SM2COOP_R_INCORRECT_SIGN 130
#define SM2COOP_R_MSG_BE_MDF 131

#define SM2COOP_R_ECP_GET_COORD_ERROR 133
#define SM2COOP_R_ECP_SET_COORD_ERROR 134
#define SM2COOP_R_ECP_CPU_ERROR 135
#define SM2COOP_R_UNABLE_TO_GET_ORD 136
#define SM2COOP_R_GEN_RAND_ERROR 137
#define SM2COOP_R_ECP_PTOOCT_ERROR 138
#define SM2COOP_R_ECK_SET_ERROR 139

#define SM2COOP_R_BN_BINTOBN_ERROR 143
#define SM2COOP_R_BN_CPU_ERROR 144
#define SM2COOP_R_BN_NOT_IN_RANGE 145
#define SM2COOP_R_BN_CP_ERROR 146

#ifdef __cplusplus
}
#endif

#endif  //OPENSSL_NO_ERR

#endif //OPENSSL_NO_SM2COOP
#endif //SM2COOP_HEADER_H

