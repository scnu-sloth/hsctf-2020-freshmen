import libnum
from gmpy2 import invert

p = 18714300200687946606417475113748411757743586023240392378853331423798582704739577160809046533982190015378916609910299982076851233748921615268428359433829002059792704988146145739860736655018941828637055243352009655261293487255469551678522883875642351671721016236035569131604259699085381596779830584046576224554770354190736563200673573024262419262559236101964171706063073640200831922815215111145006429726335055132639533551949538161314009512728921475119672731194028849975315405517071962022700366581651252088995956297543970967732767450920852567899463530316932064722349264517507350094749769497108337631790791346318230751467
q = 30552204091910875431291919425618888921607509266659604502231534635505004810638914100691545468257006240596550765690798491345098863254173424024998743532286380217457851534350524484706004447384808653484021353685996782074649108589859638965444227515165630037853803848229119739614192719714949595650173398501253949580632580378445656988567262614726587013639289383099203420083245588942219970897830391338154716916744536057329192636782494267528658701270088641884801883694117073790281623634377404263059229020529966601047901105181866246255952836387904879534241722493167641455570024588858425255243370690280787155370103141260043411661
dp = 2113650676922590921531406888097175652666553970370206386238192407439908607036913562120812895676588977437717329729051667137173845584932797476841955390760948378845188349717411244341491685723554677607214477013556813221577575765839040070466260630647631980977901292211801713522691310773154899165765446687212364661111742856414291731192429304118135217311044617930564270906487203143122481159609223562494921233557423130057191279288297384357002893710427953127663050040765484710119548288959249480276734240867985329381597554393859547626867432765689088835380447607255235739900677632980703302358871506496687657614784232363239722243
dq = 5788167388051724716810892119036276384568739745937396013142966588262653289337075487717487326501429819394838902326342940814278059196225682985490579480515715772286488419773964621864186639509899233511073564527985951512176641259265549161375785957646938340127913599774441207415776838831509697561248781879302410919530236131723614624424074189229089759925778421759786019424889546421170675540836209291930403385372726059756470641511777704976220572754195964140672876687026237952210676500280961856740738830271013035564815946324727885195243099976744409776094893483325977817127736576433569067055608588326403902580541206686303889873
c = 384929090932385996300437698443351351222657430231792271021979369045257864053158435250184030149777284082510073627528209810672363521580647440950106870825629883302323851559034735994087843688646935370662482579888504962318787263997049089413754685891026635315320875882728719395076452158893555507140577145903864388713919016157101958904142810732607134452942881617431875298933328540319148889024495933387044799699433095512815295940010646778114607098872549702858456599434456983299647009574282025979457015668597891927983237716649083484352758257963545691110984096821795178242993969192099166184429086345049153979409087585587571327817887358571118356759225035695747961543312655312264279672525598786445423631249211265717828366185415266991409347843974610048165409998344775345360487289963115672655921621317473495217757627154800133102951496287140658824930568854480305068261055037053240580934109999991985818224800202315818697854673777558125149884689730910631204781640327296146871675437493511228919215368716128657061542948569525563311760449077224551898269699919505183276551536489615118550091258023171726065399277746784797644908104579006305836735024990455916432520581462154492205029992103020811657574184733472856639500738114451844881095812082300354248726945

n = p*q

mp = pow(c, dp, p)
mq = pow(c, dq, q)
pinv = invert(p, q)
y = ((mq-mp)*pinv) % q
m = y*p+mp

m = libnum.n2s(int(m))
print(m)
