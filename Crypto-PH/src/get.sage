import libnum

p=0xb7d179681be0a7a10ce608f14cffea50afd39a59245bffbdf693d70b90e9f5290e3f3207dfbb1a846ae30dd5a0d15624eb7bbf2afbd475edd69edb0e5ddc2aeb5527f60251e309b8ca6954052ecebde40c7f814e7a8e177184db0f824bcfa569b61e9feb556ac85cb3f9603d84d4027d5e50e4d87eea836597d939d5a417eb50cd1f89b1edad20531561e05ee10dfbd68f9888c7ec39e79b3ad7114ce5331fa90a6f89ab8848a2d994923d086ba0b993c33
g=0x35f0368f3811c511bad0a6f60e9cb9aaab8942c6cdcf7a6c77996a148f185a15b64998a6d28f8c58baa1e0cf26bf12581de00bf047f62a9c1a0b0182c54f43a1cf8f55ced9ccda693bb97489a44dbfb7a86392bbacb4da3efaea036ec261c28650dd9a3cc610fcc22f8af13bff1da332939b19c0f6202adbcf9f47794e22e01aa8e60526bfa9e634ec62015d5c1b60c33fc87317f0f2777a343f9c7726919e8ef39086a5863571e35cee55a448b9bd90f55
h=0x30c6f6919b8ddafcfae3029ff3c86f6a6d6f6a034e9002d5121df464ed2cf57e3882dc67e6cd0b9733b8a318495189c99467a86123d0891aece1e0f1944e32d24f9b629cedb49bd2a3098d9654540cde81e3b33b4ad4eb49c820b25e58296afb8fe96a0485dff8869290d2380a6976401b09aefcb9c6470c2b496e55bff167df7f901fdf30280c35072e3b8c72684f79fffd8787b3732c02ab9d2775611acfff0d48dd27ebe61171ee8ae9709bdd31e1e78

n = p-1  # order
factors = prime_range(1022)

y = []
for qi in factors:  # all primes
  gi = pow(g, n//qi, p)
  hi = pow(h, n//qi, p)
  for yi in range(qi):
    if pow(gi, yi, p) == hi:
      #print('debug -> '+str(yi)+' '+str(gi)+' '+str(hi)+' '+str(qi))
      y.append(yi)
      break
  else:
    print('ERROR')
    exit(-1)

result = crt(y, factors) % (p-1)
print(libnum.n2s(int(result)))
