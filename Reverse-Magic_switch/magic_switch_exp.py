v2=[14,16,35,28,15,42,14,16,29,60,53,12,35,46,116,15,92,56,42,19,3,20,28,37,6,19,13,20,56,6,20,27,20]
fake_flag="Hahahahahahah_Th1s_is_a_f4ke_f1ag"
flag=""
for i in range(33):
    tmp=v2[i]^ord(fake_flag[i])^20
    flag+=chr(tmp)
print(flag)