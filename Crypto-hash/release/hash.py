# Hint: pycryptodome
from Crypto.PublicKey import DSA
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
import base64


p = 0x836b6009b25f6ef58b16a38508fae52f2fec89d3a42d96e8d8603aef0986c511cca9ad3f472eecba7e2f5bb4df9a7c43fa450466d61fbf196c7557b16d29dfd72bd1c595848b9168da2200b5be0557829c22d5bf23cecedad6e5b1cd80d7e23a56e18ef9c4b664bca444a2f6ae16e023bb6cdbe2484a95617c5e687a9d470c42878bcc47ebe09f2b0c7147eae1d6ac5a02a9384d6610ad9db42e5d089f6618bd23d9d6499983d545d1f4bc421d128a590be1ec6bce7b3cc1de3c63ebc8c96584fd80ffcfbc077d3429fe764258d8b599c79bb49054c9ce949dca550498e2dee187582dfe6369df8406a9b18a2c9b07167249be2ac67e6be82138b9b07522fc4b
q = 0xbffab2618c407b8e0db5b8dfe73f7786bc575a31e210d395587c6845
g = 0x49317c3daad8d368c579cd9daec93204a6c956568adbfe7327ae68af9e296aef4414271536c00a72272177c65ef2c155a1acaf4e9a0964d973a3d6b8f18caa1c5cef5ff057c862e73fa08449415a836878ca99845b344511794349ebf2cd2a2763db24bb4a269614f2f928d4433fdd1cc0c473e933a23e122dc6a5b5cb56bb095beefbdf3e7c7fe03f0989660c394dc6f5c8772b8547d10dcd4b11aa597d30c24171a625df6cc8b654a51596d0fa500896b62daf5ca89abd1db9a81973afb791f383772622c02a69a2473e02ce1a22a258693f8e543cd3799306676749a27f29e435f30f5d23fec28ce47eeb52255ad708eecca9ddfc504ad63820ff0af20ad9

def pkcs7padding(text):
    bs = AES.block_size
    length = len(text)
    bytes_length = len(bytes(text, encoding = 'utf-8'))
    padding_size = length if (bytes_length == length) else bytes_length
    padding = bs - padding_size % bs
    padding_text = chr(padding) * padding
    return text + padding_text
 
def encrypt(key, content):
    key_bytes = key.to_bytes(key_max_length, byteorder = 'big', signed = False)
    cipher = AES.new(key_bytes, AES.MODE_CBC, iv)
    content_padding = pkcs7padding(content)
    encrypt_bytes = cipher.encrypt(bytes(content_padding, encoding = 'utf-8'))
    result = str(base64.b64encode(encrypt_bytes), encoding = 'utf-8')
    return result

def power(a, b, c):
    result = 1
    while b > 0:
        if b % 2 == 1 :
            result = result * a % c
        a = a * a % c
        b >>= 1
    return result

def hashFunction(y, m, r):
    return power(g, m, p) * power(y, r, p) % p

if __name__ == "__main__":

    rand1 = 0xa0e2b51b757bdca32525e11a0b7b8c0ee2d190b4b1b1d204ecbb0037
    rand2 = 0x9d6d74d5893e16e10bcd4f12a9903457b64f95b3ecc7c7808850a60c

    pk = 0x260de05a8f19d5716ec3450ca8fde71851702892fd4f1b57487694fd9142fca75da21af6db8dcf2614b385f1d69e255367e3ae824180056a928719bac9197def7f15e9ac0501b0d87549341742b5b901563f0bc309ec5dc6e4035263d1f9d78bfe542f56bf04c927ffc1b7c98527f979273db94d03a68c9b12f2a3501ff3084cdf1c7693efb2b7f74f1e4e25db1753b6f094cefe9978f1883fd0367ef7809192cbfa87ae198b22c3f00dd191c9b5cf9a3aba3f476ef85152c3fc59243162688e9eeaca60e7f1cbe1b6083e24fe5db02de44dc676d5858153fcdafefb206c0f2b9d726a641f75ba83279bf42210baaf775e1d60a5342ced8b62ba6b3395e302cf
    
    msg1 = int(SHA256.new(b'Hello, world!').hexdigest(), 16)
    msg2 = int(SHA256.new(b'Hell0, w0rld!').hexdigest(), 16)

    if hashFunction(pk, msg1, rand1) == hashFunction(pk, msg2, rand2):
        print("The hash value of msg1 and msg2 is equal.")

    # sk = ???
    # key = DSA.construct((pk, g, p, q, sk), consistency_check = True)  # DSA.construct((y, g, p, q, x)) 
    # enc_flags = encrypt(key.x, flags)

    enc_flags = "XZpnu+F1+k5vRNu9goz3ZJz5lkK/yFcaRG1AahMwDMY="
    print("The encrypted flag is", enc_flags)

