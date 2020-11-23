#ifndef TPSM2_HEADER_H
#define TPSM2_HEADER_H

#include <openssl/opensslconf.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/objects.h>
#include <openssl/ossl_typ.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <openssl/evp.h>

#ifndef OPENSSL_NO_TPSM2

#ifdef __cplusplus
extern "C"
{
#endif
   /********************************************************************/
   /*               struct for tpsm2 client and server                 */
   /********************************************************************/

   typedef EC_KEY TPSM2_KEY;                /*tpsm2 key struct*/
   typedef struct tpsm2_srvr TPSM2_SRVR;    /*tpsm2 signature server struct*/
   typedef struct tpsm2_clnt TPSM2_CLNT;    /*tpsm2 signature client struct*/
   typedef struct tpsm2d_clnt TPSM2D_CLNT;  /*tpsm2 dec client struct*/
   typedef struct tpsm2d_srvr TPSM2D_SRVR;  /*tpsm2 dec server struct*/
   typedef struct tpsm2_skpt1 TPSM2_SK_PT1; /*tpsm2 sk partial u1 struct*/
   typedef struct tpsm2_skpt2 TPSM2_SK_PT2; /*tpsm2 sk partial u2 struct*/

   /********************************************************************/
   /*                      tpsm2 key method                            */
   /********************************************************************/

   /** Creates a new TPSM2_KEY object.
    *  \return TPSM2_KEY object or NULL if an error occurred.
    */
   TPSM2_KEY *TPSM2K_new(void);

   /** Frees a TPSM2_KEY object.
    *  \param  key  TPSM2_KEY object to be freed.
    */
   void TPSM2K_free(TPSM2_KEY *key);

   /** Generates a pair {w,hd} in TPSM2_KEY object.
    *  \param  key  TPSM2_KEY object.
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2K_key_gen(TPSM2_KEY *key);

   /** Set a W in TPSM2_KEY object.
    *  \param  key  TPSM2_KEY object.
    *  \param  w    EC_POINT object.
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2K_set_W(TPSM2_KEY *key, const EC_POINT *w);

   /** Set a hd in TPSM2_KEY object.
    *  \param  key  TPSM2_KEY object.
    *  \param  hd   BIGNUM object.
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2K_set_hd(TPSM2_KEY *key, const BIGNUM *hd);

   /** Copys a W from TPSM2_KEY object.
    *  \param  key  TPSM2_KEY object.
    *  \param  w    EC_POINT object.
    *  \return newly created EC_POINT object or NULL if an error occurred.
    */
   EC_POINT *TPSM2K_dup_W(const TPSM2_KEY *key);

   /** Returns the EC_GROUP object of a TPSM2_KEY object
    *  \param  key  TPSM2_KEY object
    *  \return the EC_GROUP object (possibly NULL).
    */
   const EC_GROUP *TPSM2K_get_group(const TPSM2_KEY *key);

   /** Returns the W object of a TPSM2_KEY object
    *  \param  key  TPSM2_KEY object
    *  \return the W EC_POINT object (possibly NULL).
    */
   const EC_POINT *TPSM2K_get_W(const TPSM2_KEY *key);

   /** Returns the hd object of a TPSM2_KEY object
    *  \param  key  TPSM2_KEY object
    *  \return the hd BIGNUM object (possibly NULL).
    */
   const BIGNUM *TPSM2K_get_hd(const TPSM2_KEY *key);

   /** Encodes a TPSM2_KEY object and stores the result in a buffer.
    *  \param  key  the TPSM2_KEY object to encode
    *  \param  out  the buffer for the result  (or NULL ,the memory is allocated inside)
    *  \param  olen  lenght of out
    *  \return lenght of out on success and 0 if an error occurred.
    */
   int TPSM2K_serialization(const TPSM2_KEY *key, unsigned char **out, size_t *olen);

   /** Decodes a TPSM2_KEY object from a memory buffer.
    *  \param  key  a pointer to a TPSM2_KEY object which should be used (or NULL)
    *  \param  in   pointer to memory with the DER encoded TPSM2_KEY key
    *  \param  inlen  length of the DER encoded TPSM2_KEY key
    *  \return the decoded TPSM2_KEY key or NULL if an error occurred.
    */
   TPSM2_KEY *TPSM2K_deserialization(TPSM2_KEY **key, const unsigned char **in, size_t inlen);

   /********************************************************************/
   /*                      tpsm2 common method                         */
   /********************************************************************/
   /*inside for TPSM2K_sign_verify*/
   int TPSM2K_sign_verify_do(const EC_POINT *Pa, const unsigned char *msg, size_t msg_len,
                             const unsigned char *uid, size_t uid_len,
                             const BIGNUM *r, const BIGNUM *s);

   /* SM2 signature verify for tmpsm2
   *  \param  Pa   public key 
   *  \param  msg  message buffer
   *  \param  msg_len message length
   *  \param  uid user id
   *  \param  uid_len length of user id
   *  \param  sig  signature buffer
   *  \param  sig_len signature buffer length
   *  \return 1 on success and 0 if an error occurred.
   */
   int TPSM2K_sign_verify(const EC_POINT *Pa, const unsigned char *msg, size_t msg_len,
                          const unsigned char *uid, size_t uid_len,
                          const unsigned char *sig, size_t sig_len);

   /** Return the length of signature buffer 
    *  \param key a TPSM2_KEY key
    *  \return length of signature buffer on success and 0 if an error occurred.
    */
   int TPSM2K_sign_size(TPSM2_KEY *key);

   /** Encodes a EC_POINT object and stores the result in a buffer.
    *  \param  point  the EC_POINT object to encode
    *  \param  group  the EC_GROUP for field
    *  \return the HEX string encoded EC_POINT or NULL if an error occurred.
    */
   char *TPSM2K_ECPoint_Serialize(const EC_POINT *point, const EC_GROUP *group);

   /** DEcodes a EC_POINT object from memory buffer
    *  \param  group  the EC_GROUP for field
    *  \param  in  pointer to memory with the HEX string encoded EC_POINT
    *  \return the decode EC_POINT or NULL if an error occurred.
    */
   EC_POINT *TPSM2K_ECPoint_Deserialize(const EC_GROUP *group, const char *in);

   /** Encodes a BIGMN object and stores the result in a buffer.
    *  \param  bignum  the BIGNUM object to encode
    *  \return the HEX string encoded EC_POINT or NULL if an error occurred.
    */
   char *TPSM2K_BIGNUM_Serialize(const BIGNUM *bignum);

   /** DEcodes a BIGNUM object from memory buffer
    *  \param  in  pointer to memory with the HEX string encoded BIGNUM
    *  \return the decode BIGNUM or NULL if an error occurred.
    */
   BIGNUM *TPSM2K_BIGNUM_Deserialize(const char *in);

   /*Compute SM2 sign extra data: e = sm3(ENTL + ID + a + b + Gx + Gy + Xa + Ya  + m)
    *  \param  group  the EC_GROUP for field
    *  \param  pk   public key 
    *  \param  uid user id
    *  \param  uid_len length of user id
    *  \param  msg  message buffer
    *  \param  msg_len message length
    *  \param  e  sm2 sign extra data
    *  \param  e_len sm2 sign extra data length  (sm3 size)
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2K_get_e(const EC_GROUP *group, const EC_POINT *pk,
                    const unsigned char *uid, int uid_len,
                    const unsigned char *msg, size_t msg_len,
                    unsigned char *e_buf, size_t *e_len);

   /********************************************************************/
   /*                   tpsm2 client signature method                  */
   /********************************************************************/

   /** Creates a new TPSM2_CLNT object.
    *  \param  key  TPSM2_KEY object that has already generated key
    *  \return TPSM2_CLNT object or NULL if an error occurred.
    */
   TPSM2_CLNT *TPSM2CLNT_new(TPSM2_KEY *key);

   /** Frees a TPSM2_CLNT object.
    *  \param  key  TPSM2_CLNT object to be freed.
    */
   void TPSM2CLNT_free(TPSM2_CLNT *clnt);

   /**  Generates a P in clnt TPSM2_CLNT object
    *  \param  clnt TPSM2_CLNT object
    *  \param  W_peer the EC_POINT from server
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2CLNT_gen_P(TPSM2_CLNT *clnt, const EC_POINT *W_peer);

   /**  Gets P from clnt TPSM2_CLNT object
    *  \param  clnt TPSM2_CLNT object
    *  \return the EC_POINT p or NULL if an error occurred.
    */
   const EC_POINT *TPSM2CLNT_get_P(TPSM2_CLNT *clnt);

   /**  Gets w_peer from clnt TPSM2_CLNT object
    *  \param  clnt TPSM2_CLNT object
    *  \return the EC_POINT w_peer or NULL if an error occurred.
    */
   const EC_POINT *TPSM2CLNT_get_W_peer(TPSM2_CLNT *clnt);

   /**  Sets public key (P) from srvr TPSM2_CLNT object
    *  \param  clnt TPSM2_CLNT object
    *  \param  P public key(P)
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2CLNT_set_P(TPSM2_CLNT *clnt, const EC_POINT *P);

   /**  Sets W_peer (w_peer) from srvr TPSM2_CLNT object
    *  \param  clnt TPSM2_CLNT object
    *  \param  W_peer 
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2CLNT_set_W_peer(TPSM2_CLNT *clnt, const EC_POINT *W_peer);

   /**  Gets TPSM2_KEY from clnt TPSM2_CLNT object
    *  \param  clnt TPSM2_CLNT object
    *  \return the TPSM2_KEY key or NULL if an error occurred.
    */
   const TPSM2_KEY *TPSM2CLNT_get_key(TPSM2_CLNT *clnt);

   /*inside for TPSM2CLNT_sign_gen_Q*/
   EC_POINT *TPSM2CLNT_sign_gen_Q_do(TPSM2_CLNT *clnt);

   /**  Generates Q 
    *  \param  clnt TPSM2_CLNT object
    *  \return the EC_POINT Q Hex string or NULL if an error occurred.
    */
   char *TPSM2CLNT_sign_gen_Q(TPSM2_CLNT *clnt);

   /*inside for TPSM2CLNT_sign_sig*/
   int TPSM2CLNT_sign_do(const TPSM2_CLNT *clnt,
                         const BIGNUM *r, const BIGNUM *s1,
                         BIGNUM *s);
   /*inside for TPSM2CLNT_sign*/
   ECDSA_SIG *TPSM2CLNT_sign_sig(const TPSM2_CLNT *clnt, const ECDSA_SIG *srvr_sig);

   /** Signature mgs in client peer 
    *  \param  clnt TPSM2_CLNT object
    *  \param  srvr_sig the signature buffer of server peer
    *  \param  srvr_sig_len the length of signature of server
    *  \param  sig  signature buffer result is generated by client peer (not NULL)
    *  \param  sig_len the length of signature buffer result
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2CLNT_sign(const TPSM2_CLNT *clnt, const unsigned char *srvr_sig, size_t srvr_sig_len,
                      unsigned char *sig, size_t *sig_len);

   /********************************************************************/
   /*                     tpsm2 client dec method                      */
   /********************************************************************/

   /** Creates a new TPSM2D_CLNT object.
    *  \param  key  TPSM2D_CLNT object that has already generated key
    *  \return TPSM2D_CLNT object or NULL if an error occurred.
    */
   TPSM2D_CLNT *TPSM2DCLNT_new(TPSM2_KEY *key);

   /** Frees a TPSM2D_CLNT object.
    *  \param  key  TPSM2D_CLNT object to be freed.
    */
   void TPSM2DCLNT_free(TPSM2D_CLNT *clnt);

   /**  Gets W from clnt TPSM2D_CLNT object
    *  \param  clnt TPSM2D_CLNT object
    *  \return the EC_POINT W or NULL if an error occurred.
    */
   const EC_POINT *TPSM2DCLNT_get_W(TPSM2D_CLNT *clnt);

   /**  Gets P from clnt TPSM2D_CLNT object
    *  \param  clnt TPSM2D_CLNT object
    *  \return the EC_POINT P or NULL if an error occurred.
    */
   const EC_POINT *TPSM2DCLNT_get_P(TPSM2D_CLNT *clnt);

   /**  Gets TPSM2_KEY key from clnt TPSM2D_CLNT object
    *  \param  clnt TPSM2D_CLNT object
    *  \return the TPSM2_KEY key or NULL if an error occurred.
    */
   const TPSM2_KEY *TPSM2DCLNT_get_key(TPSM2D_CLNT *clnt);

   /**  Generates a P in clnt TPSM2D_CLNT object
    *  \param  clnt TPSM2D_CLNT object
    *  \param  W_s the EC_POINT from server
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2DCLNT_KGen1_gen_P(const EC_POINT *W_s, TPSM2D_CLNT *clnt);

   /**  Encrypt message
    *  \param  clnt PK object
    *  \param  msg message needed be encrypted
    *  \param  msg_len length of message
    *  \param  out  the buffer for the result  (or NULL ,the memory is allocated inside)
    *  \param  olen  lenght of out
    *  \return lenght of out on success and 0 if an error occurred.
    */
   int TPSM2DCLNT_enc(const EC_POINT *PK, const unsigned char *msg, size_t msg_len, unsigned char **out, size_t *olen);

   /**  Generates C1 and CA1 in tpsm2 dec
    *  \param  clnt TPSM2D_CLNT object
    *  \param  cipher cipher text
    *  \param  cipher_len length of cipher text
    *  \param  C1 EC_POINT object generate form client peer 
    *  \param  CA1 EC_POINT object generate form client peer 
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2DCLNT_dec_gen_C(TPSM2D_CLNT *clnt, const unsigned char *cipher, size_t cipher_len, EC_POINT *C1, EC_POINT *CA1);

   /**  Decrypt message in tpsm2 dec
    *  \param  clnt TPSM2D_CLNT object
    *  \param  CS1  EC_POINT object from server
    *  \param  cipher cipher text
    *  \param  cipher_len length of cipher text
    *  \param  msg result message 
    *  \param  msg_len length of message
    *  \return lenght of out on success and 0 if an error occurred.
    */
   int TPSM2DCLNT_dec(const TPSM2D_CLNT *clnt, const EC_POINT *CS1, const unsigned char *cipher, size_t cipher_len, unsigned char **msg, size_t *msg_len);

   /********************************************************************/
   /*                   tpsm2 server signature method                  */
   /********************************************************************/

   /** Creates a new TPSM2_SRVR object.
    *  \param  key  TPSM2_SRVR object that has already generated key
    *  \return TPSM2_SRVR object or NULL if an error occurred.
    */
   TPSM2_SRVR *TPSM2SRVR_new(TPSM2_KEY *key);

   /** Frees a TPSM2_SRVR object.
    *  \param  key  TPSM2_SRVR object to be freed.
    */
   void TPSM2SRVR_free(TPSM2_SRVR *srvr);

   /**  Generates a P in srvr TPSM2_SRVR object
    *  \param  srvr TPSM2_SRVR object
    *  \param  W_peer the EC_POINT from client
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SRVR_gen_P(TPSM2_SRVR *srvr, const EC_POINT *W_peer);

   /**  Sets public key (P) from srvr TPSM2_SRVR object
    *  \param  srvr TPSM2_SRVR object
    *  \param  P public key(P)
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SRVR_set_P(TPSM2_SRVR *srvr, const EC_POINT *P);

   /**  Gets P from srvr TPSM2_SRVR object
    *  \param  srvr TPSM2_SRVR object
    *  \return the EC_POINT p or NULL if an error occurred.
    */
   const EC_POINT *TPSM2SRVR_get_P(TPSM2_SRVR *srvr);

   /**  Gets w_peer from srvr TPSM2_SRVR object
    *  \param  srvr TPSM2_SRVR object
    *  \return the EC_POINT w_peer or NULL if an error occurred.
    */
   const EC_POINT *TPSM2SRVR_get_W_peer(TPSM2_SRVR *srvr);

   /**  Gets key from srvr TPSM2_SRVR object
    *  \param  srvr TPSM2_SRVR object
    *  \return the TPSM2_KEY key or NULL if an error occurred.
    */
   const TPSM2_KEY *TPSM2SRVR_get_key(TPSM2_SRVR *srvr);

   /*inside for TPSM2SRVR_sign_sig*/
   int TPSM2SRVR_sign_do(const TPSM2_SRVR *srvr, const EC_POINT *Q,
                         const unsigned char *msg, const size_t msg_len,
                         const unsigned char *uid, int uid_len,
                         BIGNUM *r, BIGNUM *s);

   /*inside for TPSM2SRVR_sign*/
   ECDSA_SIG *TPSM2SRVR_sign_sig(const TPSM2_SRVR *srvr, const EC_POINT *Q,
                                 const unsigned char *msg, const size_t msg_len,
                                 const unsigned char *uid, int uid_len);

   /**  Generates a part of signature in server peer
    *  \param  srvr TPSM2_SRVR object
    *  \param  Q the hex string from client
    *  \param  mgs message 
    *  \param  msg_len message length
    *  \param  sig  a part of signature buffer result is generated by server peer (not NULL)
    *  \param  sig_len the length of signature buffer result
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SRVR_sign(const TPSM2_SRVR *srvr, const char *Q,
                      const unsigned char *msg, const size_t msg_len,
                      const unsigned char *uid, int uid_len,
                      unsigned char *sig, size_t *sig_len);

   /********************************************************************/
   /*                     tpsm2 server dec method                      */
   /********************************************************************/

   /** Creates a new TPSM2D_SRVR object.
    *  \param  key  TPSM2D_SRVR object that has already generated key
    *  \return TPSM2D_SRVR object or NULL if an error occurred.
    */
   TPSM2D_SRVR *TPSM2DSRVR_new(TPSM2_KEY *key);

   /** Frees a TPSM2D_SRVR object.
    *  \param  key  TPSM2D_SRVR object to be freed.
    */
   void TPSM2DSRVR_free(TPSM2D_SRVR *srvr);

   /**  Gets W from srvr TPSM2D_SRVR object
    *  \param  srvr TPSM2D_SRVR object
    *  \return the EC_POINT W or NULL if an error occurred.
    */
   const EC_POINT *TPSM2DSRVR_get_W(TPSM2D_SRVR *srvr);

   /**  Gets P from srvr TPSM2D_SRVR object
    *  \param  srvr TPSM2D_SRVR object
    *  \return the EC_POINT P or NULL if an error occurred.
    */
   const EC_POINT *TPSM2DSRVR_get_P(TPSM2D_SRVR *srvr);

   /**  Gets TPSM2_KEY key from srvr TPSM2D_SRVR object
    *  \param  srvr TPSM2D_SRVR object
    *  \return the TPSM2_KEY key or NULL if an error occurred.
    */
   const TPSM2_KEY *TPSM2DSRVR_get_key(TPSM2D_SRVR *srvr);

   /**  Generates a P in srvr TPSM2D_SRVR object
    *  \param  srvr TPSM2D_SRVR object
    *  \param  W_a the EC_POINT from client
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2DSRVR_KGen1_gen_P(const EC_POINT *W_a, TPSM2D_SRVR *srvr);

   /**  Decrypt message in server peer
    *  \param  srvr TPSM2D_SRVR object
    *  \param  C1  the EC_POINT object from client
    *  \param  CA1  the EC_POINT object from client
    *  \param  CS1 EC_POINT object generate form server peer 
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2DSRVR_dec_gen_C(const TPSM2D_SRVR *srvr, const EC_POINT *C1, const EC_POINT *CA1, EC_POINT *CS1);

   /********************************************************************/
   /*                  update 2019.10.1                                */
   /********************************************************************/

   /********************************************************************/
   /*                   tpsm2  SKPartial(U1) method                    */
   /********************************************************************/

   /** Creates a new TPSM2_SK_PT1 object.
    *  \return TPSM2_SK_PT1 object or NULL if an error occurred.
    */
   TPSM2_SK_PT1 *TPSM2SKPT1_new(void);

   /** Free a TPSM2_SK_PT1 object.
    *  \param  skpt1  TPSM2_SK_PT1 object to be freed.
    */
   void TPSM2SKPT1_free(TPSM2_SK_PT1 *skpt1);

   /** Generates a pair {w,k} in TPSM2_SK_PT1 object.
    *  \param  skpt1  TPSM2_SK_PT1 object.
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT1_gen_W(TPSM2_SK_PT1 *skpt1);

   /**  Gets k  from  skpt1 object
    *  \param  skpt1 TPSM2_SK_PT1 object
    *  \return the BIGNUM k or NULL if an error occurred.
    */
   const BIGNUM *TPSM2SKPT1_get_k(TPSM2_SK_PT1 *skpt1);

   /**  Set w1 into  skpt1 object
    *  \param  skpt1 TPSM2_SK_PT1 object
    *  \param  w1 EC_POINT object 
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT1_set_W(TPSM2_SK_PT1 *skpt1, const EC_POINT *W1);

   /**  Gets W1  from  skpt1 object
    *  \param  skpt1 TPSM2_SK_PT1 object
    *  \return the EC_POINT W1 or NULL if an error occurred.
    */
   const EC_POINT *TPSM2SKPT1_get_W(TPSM2_SK_PT1 *sktp1);

   /**  Set k1 into  skpt1 object
    *  \param  skpt1 TPSM2_SK_PT1 object
    *  \param  k1 BIGNUM object 
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT1_set_k(TPSM2_SK_PT1 *skpt1, const BIGNUM *K1);

   /**  Gets hd  from  skpt1 object
    *  \param  skpt1 TPSM2_SK_PT1 object
    *  \return the BIGNUM hd or NULL if an error occurred.
    */
   const BIGNUM *TPSM2SKPT1_get_hd(TPSM2_SK_PT1 *skpt1);

   /**  Set hd into  skpt1 object
    *  \param  skpt1 TPSM2_SK_PT1 object
    *  \param  hd BIGNUM object 
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT1_set_hd(TPSM2_SK_PT1 *skpt1, const BIGNUM *hd1);

   /**  partial the d_a to hd1 and hd2
    *  \param  skpt1 TPSM2_SK_PT1 object
    *  \param  d_a BIGNUM object that is private key
    *  \param  W2 EC_POINT object that is from U2
    *  \param  c the output result (must be NULL that the memory is allocated inside)
    *  \param  clen the length of c
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT1_partial(TPSM2_SK_PT1 *sktp1, const BIGNUM *d_a, const EC_POINT *W2, unsigned char **c, size_t *clen);

   /**  make TPSM2SKPT1 object to EC_KEY for signature or encryption
    *  \param  skpt1 TPSM2_SK_PT1 object
    *  \param  key EC_KEY object (not NULL)
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT1_tran_tpsm2_key(const TPSM2_SK_PT1 *skpt1, EC_KEY *key);

   /********************************************************************/
   /*                   tpsm2  SKPartial(U2) method                    */
   /********************************************************************/

   /** Creates a new TPSM2_SK_PT2 object.
    *  \return TPSM2_SK_PT2 object or NULL if an error occurred.
    */
   TPSM2_SK_PT2 *TPSM2SKPT2_new(void);

   /** Free a TPSM2_SK_PT2 object.
    *  \param  skpt2  TPSM2_SK_PT2 object to be freed.
    */
   void TPSM2SKPT2_free(TPSM2_SK_PT2 *skpt2);

   /** Generates a pair {w,k} in TPSM2_SK_PT2 object.
    *  \param  skpt2  TPSM2_SK_PT2 object.
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT2_gen_W(TPSM2_SK_PT2 *skpt2);

   /**  Gets k  from  skpt2 object
    *  \param  skpt2 TPSM2_SK_PT2 object
    *  \return the BIGNUM k or NULL if an error occurred.
    */
   const BIGNUM *TPSM2SKPT2_get_k(TPSM2_SK_PT2 *skpt2);

   /**  Set w2 into  skpt2 object
    *  \param  skpt2 TPSM2_SK_PT2 object
    *  \param  w2 EC_POINT object 
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT2_set_W(TPSM2_SK_PT2 *skpt2, const EC_POINT *W2);

   /**  Gets W2 from  skpt2 object
    *  \param  skpt2 TPSM2_SK_PT2 object
    *  \return the EC_POINT W2 or NULL if an error occurred.
    */
   const EC_POINT *TPSM2SKPT2_get_W(TPSM2_SK_PT2 *skpt2);

   /**  Set K into  skpt2 object
    *  \param  skpt2 TPSM2_SK_PT2 object
    *  \param  k2 BIGNUM object 
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT2_set_k(TPSM2_SK_PT2 *skpt2, const BIGNUM *K2);

   /**  Gets hd  from  skpt2 object
    *  \param  skpt2 TPSM2_SK_PT2 object
    *  \return the BIGNUM hd or NULL if an error occurred.
    */
   const BIGNUM *TPSM2SKPT2_get_hd(TPSM2_SK_PT2 *skpt2);

   /**  Set hd into  skpt2 object
    *  \param  skpt2 TPSM2_SK_PT2 object
    *  \param  hd BIGNUM object 
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT2_set_hd(TPSM2_SK_PT2 *skpt2, const BIGNUM *hd2);

   /**  partial the d_a to hd1 and hd2, and here, U2 will get hd2 from c
    *  \param  skpt2 TPSM2_SK_PT2 object
    *  \param  W1 EC_POINT object that is from U1
    *  \param  c that is from U1
    *  \param  clen the length of c
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT2_partial(TPSM2_SK_PT2 *skpt2, const EC_POINT *W1, const unsigned char *c, size_t clen);

   /**  make TPSM2SKPT2 object to EC_KEY for signature or encryption
    *  \param  skpt2 TPSM2_SK_PT2 object
    *  \param  key EC_KEY object (not NULL)
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2SKPT2_tran_tpsm2_key(const TPSM2_SK_PT2 *skpt2, EC_KEY *key);

   /********************************************************************/
   /*                   tpsm2  TPSM2Dec(A) method                      */
   /********************************************************************/

   /**  Gets c1  from  cipher object
    *  \param  key TPSM2_KEY object
    *  \param  cipher  cipher text
    *  \param  clen the size of cipher
    *  \param  c1  the output c1 (not null)
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2Dec_get_C1(const TPSM2_KEY *key, const unsigned char *cipher, size_t clen, EC_POINT *C1);

   /**  decrypto messgae
    *  \param  key TPSM2_KEY object
    *  \param  c1  EC_POINT object
    *  \param  cs1 EC_POINT object from s
    *  \param  cipher  cipher text
    *  \param  clen the size of cipher
    *  \param  msg the output result (must be NULL that the memory is allocated inside)
    *  \param  mlen the length of c
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2Dec_dec_msg(const TPSM2_KEY *key, const EC_POINT *C1, const EC_POINT *CS1, const unsigned char *cipher, size_t clen, unsigned char **msg, size_t *mlen);

   /********************************************************************/
   /*                   tpsm2  TPSM2Dec(S) method                      */
   /********************************************************************/

   /**  Gets cs1  
    *  \param  key TPSM2_KEY object
    *  \param  c1  EC_POINT object from c
    *  \param  cs  the output cs1 (not null)
    *  \return 1 on success and 0 if an error occurred.
    */
   int TPSM2Dec_get_CS1(const TPSM2_KEY *key, const EC_POINT *C1, EC_POINT *CS1);

   void TPSM2Rand_seed_init();

#ifdef __cplusplus
}
#endif

/********************************************************************/
/*                    ERROR CODE FOR FUNCTION                       */
/********************************************************************/
#ifndef OPENSSL_NO_ERR
#ifdef __cplusplus
extern "C"
{
#endif

#include <openssl/err.h>
#define TPSM2err(f, r) ERR_PUT_error(ERR_LIB_TPSM2, (f), (r), __FILE__, __LINE__)

   int ERR_load_TPSM2_strings(void);
/*
 * SM2 function codes.
 */
#define TPSM2_F_K_NEW 120
#define TPSM2_F_KW_GEN 120
#define TPSM2_F_KP_GEN 121
#define TPSM2_F_CLIENT_SIG_PER 122
#define TPSM2_F_CLNT_NEW 123
#define TPSM2_F_SERVR_NEW 124
#define TPSM2_F_SERVR_SIG 125
#define TPSM2_F_CLIENT_SIG 126
#define TPSM2_F_SM2_VERIFY 127
#define TPSM2_F_ECPOINT_SERIALIZATION 128
#define TPSM2_F_ECPOINT_DESERIALIZATION 129
#define TPSM2_F_SM2_GET_Z 130
#define TPSM2_F_BIGNUM_SERIALIZATION 131
#define TPSM2_F_BIGNUM_DESERIALIZATION 132

#define TPSM2D_F_CLNT_NEW 136
#define TPSM2D_F_SERVR_NEW 137
#define TPSM2D_F_KP_GEN 138
#define TPSM2D_F_CLNET_ENC 139
#define TPSM2D_F_CLNET_GEN_C 140
#define TPSM2D_F_SERVR_GEN_C 141
#define TPSM2D_F_CLNET_DEC 142

#define TPSM2_F_SK_U1_PARTIAL 150
#define TPSM2_F_SK_U2_PARTIAL 151
#define TPSM2_F_SK_U1_NEW 152
#define TPSM2_F_SK_U2_NEW 153
#define TPSM2_F_SK_U1_GEN_W 154
#define TPSM2_F_SK_U2_GEN_W 155
#define TPSM2_F_SK_U1_GET_W 156
#define TPSM2_F_SK_U2_GET_W 157
#define TPSM2_F_SK_U1_GET_K 158
#define TPSM2_F_SK_U2_GET_K 159
#define TPSM2_F_SK_U1_SET_W 160
#define TPSM2_F_SK_U2_SET_W 161
#define TPSM2_F_SK_U1_SET_K 162
#define TPSM2_F_SK_U2_SET_K 163
#define TPSM2_F_SK_U1_GET_HD 164
#define TPSM2_F_SK_U2_GET_HD 165
#define TPSM2_F_SK_U1_TRANS_KEY 166
#define TPSM2_F_SK_U2_TRANS_KEY 167

#define TPSM2DEC_GET_C1 170
#define TPSM2DEC_GET_CS1 171
#define TPSM2DEC_DEC_MSG 172

/*
 * SM2 reason codes.
 */

#define TPSM2_R_PARAMS_NULL_ERROR 120
#define TPSM2_R_OUT_LEN_TOO_SMALL_ERROR 121
#define TPSM2_R_KEY_IS_NULL 122
#define TPSM2_R_SIG_ERROR 123
#define TPSM2_R_ENC_ERROR 124

#ifdef __cplusplus
}
#endif

#endif

#endif /*OPENSSL_NO_TPSM2*/
#endif