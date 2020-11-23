import libnum
from gmpy2 import invert

n = 31648734237121093449062759741858353305299887460770378610317325262532812380992998717086045560716165196764876375024736812043316931187449612112014480335819632714635828887393277480117469682571740475521815029501119616029222685021833456834860463301835674320610441456152948762730967186631332998314439886858424113209771045636380932420113750370162135069772576775040641310241869572513488894613647466722538462125698729611696700513321039673589745449355070643639740553615493170049122321689282686291783694560650322957955382056776701778000873105279611461240600373669009171156764610102006874690207503067227784467578546117377910059849
e = 65537
c = 8472470163184012462000528080165090036188635885351596354139960232632956476301235845514827002690956926418292313944863809902769808978125514574094431792449203362125295767224649917756465720590402146607448107700602949310739551154185709505943529176162811567787744455172636958664487513824170824375184591735235862997624339895241609184318108298806242891811364998857087830133524421290948873392796863425163637415895626597006868886489528223728832282320568060824925378471122592356209291540463778941231812179060437264730095781564995912183149503687379604059903141658253650016548620225566653730700129092787790523080898273898653528474
d = invert(e, n-1)

m = pow(c, d, n)
m = libnum.n2s(int(m))
print(m)
