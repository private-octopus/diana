
#!/usr/bin/python
# coding=utf-8
#
# Produce summaries of the data per specific column list

import sys
import codecs
from enum import Enum
import copy
import traceback
import datetime
import m3name
import captures

country_list = [["Andorra","AD","AND"],
["United Arab Emirates","AE","ARE"],
["Afghanistan","AF","AFG"],
["Antigua and Barbuda","AG","ATG"],
["Anguilla","AI","AIA"],
["Albania","AL","ALB"],
["Armenia","AM","ARM"],
["Netherlands Antilles","AN","ANT"],
["Angola","AO","AGO"],
["Antarctica","AQ","ATA"],
["Argentina","AR","ARG"],
["American Samoa","AS","ASM"],
["Austria","AT","AUT"],
["Australia","AU","AUS"],
["Aruba","AW","ABW"],
["Aland Islands","AX","ALA"],
["Azerbaijan","AZ","AZE"],
["Bosnia and Herzegovina","BA","BIH"],
["Barbados","BB","BRB"],
["Bangladesh","BD","BGD"],
["Belgium","BE","BEL"],
["Burkina Faso","BF","BFA"],
["Bulgaria","BG","BGR"],
["Bahrain","BH","BHR"],
["Burundi","BI","BDI"],
["Benin","BJ","BEN"],
["Saint-Barthelemy","BL","BLM"],
["Bermuda","BM","BMU"],
["Brunei Darussalam","BN","BRN"],
["Bolivia","BO","BOL"],
["Brazil","BR","BRA"],
["Bahamas","BS","BHS"],
["Bhutan","BT","BTN"],
["Bouvet Island","BV","BVT"],
["Botswana","BW","BWA"],
["Belarus","BY","BLR"],
["Belize","BZ","BLZ"],
["Canada","CA","CAN"],
["Cocos (Keeling) Islands","CC","CCK"],
["Congo, (Kinshasa)","CD","COD"],
["Central African Republic","CF","CAF"],
["Congo (Brazzaville)","CG","COG"],
["Switzerland","CH","CHE"],
["Cote d'Ivoire","CI","CIV"],
["Cook Islands ","CK","COK"],
["Chile","CL","CHL"],
["Cameroon","CM","CMR"],
["China","CN","CHN"],
["Colombia","CO","COL"],
["Costa Rica","CR","CRI"],
["Cuba","CU","CUB"],
["Cape Verde","CV","CPV"],
["Christmas Island","CX","CXR"],
["Cyprus","CY","CYP"],
["Czech Republic","CZ","CZE"],
["Germany","DE","DEU"],
["Djibouti","DJ","DJI"],
["Denmark","DK","DNK"],
["Dominica","DM","DMA"],
["Dominican Republic","DO","DOM"],
["Algeria","DZ","DZA"],
["Ecuador","EC","ECU"],
["Estonia","EE","EST"],
["Egypt","EG","EGY"],
["Western Sahara","EH","ESH"],
["Eritrea","ER","ERI"],
["Spain","ES","ESP"],
["Ethiopia","ET","ETH"],
["Finland","FI","FIN"],
["Fiji","FJ","FJI"],
["Falkland Islands (Malvinas) ","FK","FLK"],
["Micronesia, Federated States of","FM","FSM"],
["Faroe Islands","FO","FRO"],
["France","FR","FRA"],
["Gabon","GA","GAB"],
["United Kingdom","GB","GBR"],
["Grenada","GD","GRD"],
["Georgia","GE","GEO"],
["French Guiana","GF","GUF"],
["Guernsey","GG","GGY"],
["Ghana","GH","GHA"],
["Gibraltar ","GI","GIB"],
["Greenland","GL","GRL"],
["Gambia","GM","GMB"],
["Guinea","GN","GIN"],
["Guadeloupe","GP","GLP"],
["Equatorial Guinea","GQ","GNQ"],
["Greece","GR","GRC"],
["South Georgia and the South Sandwich Islands","GS","SGS"],
["Guatemala","GT","GTM"],
["Guam","GU","GUM"],
["Guinea-Bissau","GW","GNB"],
["Guyana","GY","GUY"],
["Hong Kong, SAR China","HK","HKG"],
["Heard and Mcdonald Islands","HM","HMD"],
["Honduras","HN","HND"],
["Croatia","HR","HRV"],
["Haiti","HT","HTI"],
["Hungary","HU","HUN"],
["Indonesia","ID","IDN"],
["Ireland","IE","IRL"],
["Israel","IL","ISR"],
["Isle of Man ","IM","IMN"],
["India","IN","IND"],
["British Indian Ocean Territory","IO","IOT"],
["Iraq","IQ","IRQ"],
["Iran, Islamic Republic of","IR","IRN"],
["Iceland","IS","ISL"],
["Italy","IT","ITA"],
["Jersey","JE","JEY"],
["Jamaica","JM","JAM"],
["Jordan","JO","JOR"],
["Japan","JP","JPN"],
["Kenya","KE","KEN"],
["Kyrgyzstan","KG","KGZ"],
["Cambodia","KH","KHM"],
["Kiribati","KI","KIR"],
["Comoros","KM","COM"],
["Saint Kitts and Nevis","KN","KNA"],
["Korea (North)","KP","PRK"],
["Korea (South)","KR","KOR"],
["Kuwait","KW","KWT"],
["Cayman Islands ","KY","CYM"],
["Kazakhstan","KZ","KAZ"],
["Lao PDR","LA","LAO"],
["Lebanon","LB","LBN"],
["Saint Lucia","LC","LCA"],
["Liechtenstein","LI","LIE"],
["Sri Lanka","LK","LKA"],
["Liberia","LR","LBR"],
["Lesotho","LS","LSO"],
["Lithuania","LT","LTU"],
["Luxembourg","LU","LUX"],
["Latvia","LV","LVA"],
["Libya","LY","LBY"],
["Morocco","MA","MAR"],
["Monaco","MC","MCO"],
["Moldova","MD","MDA"],
["Montenegro","ME","MNE"],
["Saint-Martin (French part)","MF","MAF"],
["Madagascar","MG","MDG"],
["Marshall Islands","MH","MHL"],
["Macedonia, Republic of","MK","MKD"],
["Mali","ML","MLI"],
["Myanmar","MM","MMR"],
["Mongolia","MN","MNG"],
["Macao, SAR China","MO","MAC"],
["Northern Mariana Islands","MP","MNP"],
["Martinique","MQ","MTQ"],
["Mauritania","MR","MRT"],
["Montserrat","MS","MSR"],
["Malta","MT","MLT"],
["Mauritius","MU","MUS"],
["Maldives","MV","MDV"],
["Malawi","MW","MWI"],
["Mexico","MX","MEX"],
["Malaysia","MY","MYS"],
["Mozambique","MZ","MOZ"],
["Namibia","NA","NAM"],
["New Caledonia","NC","NCL"],
["Niger","NE","NER"],
["Norfolk Island","NF","NFK"],
["Nigeria","NG","NGA"],
["Nicaragua","NI","NIC"],
["Netherlands","NL","NLD"],
["Norway","NO","NOR"],
["Nepal","NP","NPL"],
["Nauru","NR","NRU"],
["Niue ","NU","NIU"],
["New Zealand","NZ","NZL"],
["Oman","OM","OMN"],
["Panama","PA","PAN"],
["Peru","PE","PER"],
["French Polynesia","PF","PYF"],
["Papua New Guinea","PG","PNG"],
["Philippines","PH","PHL"],
["Pakistan","PK","PAK"],
["Poland","PL","POL"],
["Saint Pierre and Miquelon ","PM","SPM"],
["Pitcairn","PN","PCN"],
["Puerto Rico","PR","PRI"],
["Palestinian Territory","PS","PSE"],
["Portugal","PT","PRT"],
["Palau","PW","PLW"],
["Paraguay","PY","PRY"],
["Qatar","QA","QAT"],
["Reunion","RE","REU"],
["Romania","RO","ROU"],
["Serbia","RS","SRB"],
["Russian Federation","RU","RUS"],
["Rwanda","RW","RWA"],
["Saudi Arabia","SA","SAU"],
["Solomon Islands","SB","SLB"],
["Seychelles","SC","SYC"],
["Sudan","SD","SDN"],
["Sweden","SE","SWE"],
["Singapore","SG","SGP"],
["Saint Helena","SH","SHN"],
["Slovenia","SI","SVN"],
["Svalbard and Jan Mayen Islands ","SJ","SJM"],
["Slovakia","SK","SVK"],
["Sierra Leone","SL","SLE"],
["San Marino","SM","SMR"],
["Senegal","SN","SEN"],
["Somalia","SO","SOM"],
["Suriname","SR","SUR"],
["South Sudan","SS","SSD"],
["Sao Tome and Principe","ST","STP"],
["El Salvador","SV","SLV"],
["Syrian Arab Republic (Syria)","SY","SYR"],
["Swaziland","SZ","SWZ"],
["Turks and Caicos Islands ","TC","TCA"],
["Chad","TD","TCD"],
["French Southern Territories","TF","ATF"],
["Togo","TG","TGO"],
["Thailand","TH","THA"],
["Tajikistan","TJ","TJK"],
["Tokelau ","TK","TKL"],
["Timor-Leste","TL","TLS"],
["Turkmenistan","TM","TKM"],
["Tunisia","TN","TUN"],
["Tonga","TO","TON"],
["Turkey","TR","TUR"],
["Trinidad and Tobago","TT","TTO"],
["Tuvalu","TV","TUV"],
["Taiwan, Republic of China","TW","TWN"],
["Tanzania, United Republic of","TZ","TZA"],
["Ukraine","UA","UKR"],
["Uganda","UG","UGA"],
["US Minor Outlying Islands","UM","UMI"],
["United States of America","US","USA"],
["Uruguay","UY","URY"],
["Uzbekistan","UZ","UZB"],
["Holy See (Vatican City State)","VA","VAT"],
["Saint Vincent and Grenadines","VC","VCT"],
["Venezuela (Bolivarian Republic)","VE","VEN"],
["British Virgin Islands","VG","VGB"],
["Virgin Islands, US","VI","VIR"],
["Viet Nam","VN","VNM"],
["Vanuatu","VU","VUT"],
["Wallis and Futuna Islands ","WF","WLF"],
["Samoa","WS","WSM"],
["Yemen","YE","YEM"],
["Mayotte","YT","MYT"],
["South Africa","ZA","ZAF"],
["Zambia","ZM","ZMB"],
["Zimbabwe","ZW","ZWE"]]

def cc_to_index(ccx):
    cc = ccx.upper()
    low = 0
    high = len(country_list) -1
    if cc < country_list[low][1] or cc > country_list[high][1]:
        return -1
    elif cc == country_list[low][1]:
        return low
    elif cc == country_list[high][1]:
        return high
    else:
       while low + 1 < high:
           middle = int((low + high)/2)
           if cc == country_list[middle][1]:
               return middle
           elif cc < country_list[middle][1]:
               high = middle
           else:
               low = middle
    return -1

def cc_to_iso3(cc):
    i = cc_to_index(cc)
    if i < 0:
        return "???"
    else:
        return country_list[i][2]

class projection(Enum):
    country = 1
    city = 2
    country_day = 3
    country_weekday = 4
    country_hour = 5

class m3summary_line():
    default_address_id = "aa00"
    default_date = "2020-01-01"
    default_weekday = [
        "2020-01-06", "2020-01-07", "2020-01-08", "2020-01-09", "2020-01-10", "2020-01-11", "2020-01-12"]
    default_hour = "00:00:00"
    default_minute = ":00:00"
    default_city = "zzz"

    def __init__(self):
        self.address_id = ""
        self.cc = ""
        self.city = ""
        self.date = ""
        self.hour = ""
        self.duration = 0
        self.nb_queries = 0
        self.nb_nx_domains = 0
        self.nb_home = 0
        self.nb_corp = 0
        self.nb_mail = 0

    def load(self, line):
        parts = line.split(",")
        try:
            if len(parts) == 11 and parts[1] == "CC" and parts[2] == "City" and parts[3] == "Date":
                return 1
            self.address_id = parts[0].strip()
            self.cc = parts[1].strip()
            self.city = parts[2].strip()
            self.date = parts[3].strip()
            self.hour = parts[4].strip()
            self.duration = int(parts[5])
            self.nb_queries = int(parts[6])
            self.nb_nx_domains = int(parts[7])
            self.nb_home = int(parts[8])
            self.nb_corp = int(parts[9])
            self.nb_mail = int(parts[10])
        except:
            return -1
        return 0

    def load_m3(self, file_name):
        m3n = m3name.m3name()
        if m3n.parse_file_id(file_name) != 0:
            return -1
        capture = captures.capture_file()
        if capture.load(file_name) != 0:
            return -1
        self.address_id = m3n.address_id
        self.cc = m3n.country_code
        self.city = m3n.city_code
        self.date = m3n.m3_date
        self.hour = m3n.m3_hour
        self.duration = m3n.duration
        c0 = capture.find("root-QR", 0, 0, "")
        c1 = capture.find("root-QR", 0, 3, "")
        self.nb_queries = c0 + c1
        self.nb_nx_domains = c1
        self.nb_home = capture.find("LeakedTLD", 1, 0, "HOME")
        self.nb_corp = capture.find("LeakedTLD", 1, 0, "CORP")
        self.nb_mail = capture.find("LeakedTLD", 1, 0, "MAIL")
        return 0

    def to_string(self):
        s = self.address_id + ","
        s += self.cc + ","
        s += self.city  + "," 
        s += self.date  + ","
        s += self.hour + ","
        s += str(self.duration) + ","
        s += str(self.nb_queries) + ","
        s += str(self.nb_nx_domains) + ","
        s += str(self.nb_home) + ","
        s += str(self.nb_corp) + ","
        s += str(self.nb_mail)
        return s;

    def title_line():
        s = "address,cc,city,date,hour,duration,queries,nx_domain,home,corp,mail"
        return s

    def add(self, other):
        self.duration += other.duration
        self.nb_queries += other.nb_queries
        self.nb_nx_domains += other.nb_nx_domains
        self.nb_home += other.nb_home
        self.nb_corp += other.nb_corp
        self.nb_mail += other.nb_mail

    def project(self, p_enum):
        p = copy.deepcopy(self)
        if p_enum == projection.country:
            p.address_id = m3summary_line.default_address_id
            p.city = m3summary_line.default_city
            p.date = m3summary_line.default_date
            p.hour = m3summary_line.default_hour
        elif p_enum == projection.city:
            p.address_id = m3summary_line.default_address_id
            p.date = m3summary_line.default_date
            p.hour = m3summary_line.default_hour
        elif p_enum == projection.country_day:
            p.address_id = m3summary_line.default_address_id
            p.city = m3summary_line.default_city
            p.hour = m3summary_line.default_hour
        elif p_enum == projection.country_weekday:
            p.address_id = m3summary_line.default_address_id
            p.city = m3summary_line.default_city
            p.hour = m3summary_line.default_hour
            try:
                datepart = p.date.split("-")
                dt = datetime.datetime(int(datepart[0]),int(datepart[1]),int(datepart[2]))
                p.date = m3summary_line.default_weekday[dt.weekday()]
            except:
                print("Cannot set date: " + datepart[0] + "-" + datepart[1]+ "-" + datepart[2])
                p.date = m3summary_line.default_weekday[0]
        elif p_enum == projection.country_hour:
            p.address_id = m3summary_line.default_address_id
            p.city = m3summary_line.default_city
            p.date = m3summary_line.default_date
            hpart = p.hour.split(":")
            if len(hpart) == 3:
                p.hour = hpart[0] + m3summary_line.default_minute
            else:
                p.hour = m3summary_line.default_hour
        else:
            raise ValueError("Unsupported projection")
        return p

    def compare_key(self, other):
        if (self.cc < other.cc):
            return -1
        elif (self.cc > other.cc):
            return 1
        elif (self.city < other.city):
            return -1
        elif (self.city > other.city):
            return 1
        elif (self.date < other.date):
            return -1
        elif (self.date > other.date):
            return 1
        elif (self.address_id < other.address_id):
            return -1
        elif (self.address_id > other.address_id):
            return 1
        elif (self.date < other.date):
            return -1
        elif (self.date > other.date):
            return 1
        elif (self.hour < other.hour):
            return -1
        elif (self.hour > other.hour):
            return 1
        else:
            return 0

    def compare(self, other):
        ret = self.compare_key(other)
        if ret != 0:
            return ret
        elif (self.duration < other.duration):
            return -1
        elif (self.duration > other.duration):
            return 1
        elif (self.nb_queries < other.nb_queries):
            return -1
        elif (self.nb_queries > other.nb_queries):
            return 1
        elif (self.nb_nx_domains< other.nb_nx_domains):
            return -1
        elif (self.nb_nx_domains > other.nb_nx_domains):
            return 1
        elif (self.nb_home < other.nb_home):
            return -1
        elif (self.nb_home > other.nb_home):
            return 1
        elif (self.nb_corp < other.nb_corp):
            return -1
        elif (self.nb_corp > other.nb_corp):
            return 1
        elif (self.nb_mail < other.nb_mail):
            return -1
        elif (self.nb_mail > other.nb_mail):
            return 1
        else:
            return 0
    
    def __lt__(self, other):
        return self.compare(other) < 0
    def __gt__(self, other):
        return self.compare(other) > 0
    def __eq__(self, other):
        return self.compare(other) == 0
    def __le__(self, other):
        return self.compare(other) <= 0
    def __ge__(self, other):
        return self.compare(other) >= 0
    def __ne__(self, other):
        return self.compare(other) != 0

class m3summary_list:
    def __init__(self):
        self.summary_list = []

    def load_line(self, line):
        m3l = m3summary_line()
        ret = m3l.load(line)
        if ret == 0:
            self.summary_list.append(m3l)
        return ret

    def load_file(self, file_name):
        try:
            sum_file = codecs.open(file_name, "r", "UTF-8")
            nb_fail = 0
            for line in sum_file:
                ret = self.load_line(line)
                if ret == -1:
                    if nb_fail == 0:
                        print("Error, cannot parse: " + line)
                    nb_fail += 1
            sum_file.close()
            if nb_fail > 1:
                print("Could not parse " + str(nb_fail) + " lines.")
            if len(self.summary_list) == 0:
                print("File is empty")
                return -1
            return 0
        except Exception:
            traceback.print_exc()
            print("Cannot open <" + file_name + ">");
            return -1

    def save_file(self, file_name):
        try:
            sum_file = codecs.open(file_name, "w", "UTF-8")
            sum_file.write(m3summary_line.title_line() + "\n")
            for summary in self.summary_list:
                sum_file.write(summary.to_string() + "\n");
            sum_file.close()
            return 0
        except Exception:
            traceback.print_exc()
            print("Cannot open <" + file_name + ">");
            return -1

    def project(self, p_enum):
        raw_p = []
        for summary in self.summary_list:
            raw_p.append(summary.project(p_enum))
        raw_p.sort()
        i = 1
        projected = []
        p = raw_p[0]
        while i < len(raw_p):
            if p.compare_key(raw_p[i]) == 0:
                p.add(raw_p[i])
            else:
                projected.append(p)
                p = raw_p[i]
            i += 1
        projected.append(p)
        return projected

# self_test function

def cc_to_iso3_test():
    cc_test = ["aa", "ad", "ap", "gm", "om", "on", "zw", "zz"]
    cc_index = [-1, 0, -1, 83, 170, -1, 246, -1]
    cc_iso3 = ["???", "AND", "???", "GMB", "OMN", "???", "ZWE", "???"]

    r = 0
    i = 0
    while i < len(cc_test):
        x = cc_to_index(cc_test[i])
        if x != cc_index[i]:
            print("Found index " + str(x) + " for <" + cc_test[i] + "> instead of " + str(cc_index[i]))
            r = -1
        i3 = cc_to_iso3(cc_test[i])
        if i3 != cc_iso3[i]:
            print("Found iso3 " + i3 + " for <" + cc_test[i] + "> instead of " + cc_iso3[i])
            r = -1
        i += 1
    return r

def m3summary_line_test():
    def test_projection(m3l, p_enum, p_ref):
        r = 0
        pcc = m3l.project(p_enum)
        if pcc.to_string() != p_ref[i]:
            print("p(" + str(p_enum) + ": " + pcc.to_string() + "\n    for: " + p_ref[i])
            r = -1
        return r

    test_cases = [
        "address_id,CC,City,Date,Hour,Duration,nb_queries,Nb_NX_Domain,Nb_Home,Nb_Corp,Nb_Mail",
        "aa01,br,sjk,2019-08-03,06:17:58,300,38,8,0,0,0",
        "aa05,us,lax,2019-08-03,18:36:45,300,152625,102924,4619,1290,0",
        "xxx, 1, 2, 3, 4, 5",
        "aa05,us,lax,2019-08-03,18:36:45,300,NaN,102924,4619,1290,0",
        ]
    test_return = [ 1, 0, 0, -1, -1]
    test_cc = [ "", "br", "us", "", ""]
    test_nb_queries = [ 0, 38, 152625, 0, 0]
    proj_cases = [
        "aa01,br,sjk,2019-08-03,06:17:58,300,38,8,0,0,0",
        "aa05,us,lax,2019-08-05,18:36:45,300,152625,102924,4619,1290,0"]
    proj_country = [
        "aa00,br,zzz,2020-01-01,00:00:00,300,38,8,0,0,0",
        "aa00,us,zzz,2020-01-01,00:00:00,300,152625,102924,4619,1290,0"]
    proj_city = [
        "aa00,br,sjk,2020-01-01,00:00:00,300,38,8,0,0,0",
        "aa00,us,lax,2020-01-01,00:00:00,300,152625,102924,4619,1290,0"]
    proj_country_day = [
        "aa00,br,zzz,2019-08-03,00:00:00,300,38,8,0,0,0",
        "aa00,us,zzz,2019-08-05,00:00:00,300,152625,102924,4619,1290,0"]
    proj_country_weekday = [
        "aa00,br,zzz,2020-01-11,00:00:00,300,38,8,0,0,0",
        "aa00,us,zzz,2020-01-06,00:00:00,300,152625,102924,4619,1290,0"]
    proj_country_hour = [
        "aa00,br,zzz,2020-01-01,06:00:00,300,38,8,0,0,0",
        "aa00,us,zzz,2020-01-01,18:00:00,300,152625,102924,4619,1290,0"]

    i = 0
    r = 0
    while i < len(test_cases):
        m3l = m3summary_line()
        ret = m3l.load(test_cases[i])
        if ret != test_return[i]:
            print("Returned " + str(ret) + " for: " + test_cases[i])
            r = -1
        elif ret == 0:
            if m3l.cc != test_cc[i]:
                print("CC: " + str(m3l.cc) + " for: " + test_cases[i])
                r = -1
            elif m3l.nb_queries != test_nb_queries[i]:
                print("nb_queries: " + str(m3l.nb_queries) + " for: " + test_cases[i])
                r = -1
            elif m3l.to_string() != test_cases[i]:
                print("Got str: " + m3l.to_string() + "\n    for:" + test_cases[i])
                r = -1
        i += 1

    i = 0
    while i < len(proj_cases):
        m3l = m3summary_line()
        ret = m3l.load(proj_cases[i])
        if ret != 0:
            print("Returned " + str(ret) + " for: " + proj_cases[i])
            r = -1
        else:
            r += test_projection(m3l, projection.country, proj_country)
            r += test_projection(m3l, projection.city, proj_city)
            r += test_projection(m3l, projection.country_day, proj_country_day)
            r += test_projection(m3l, projection.country_weekday, proj_country_weekday)
            r += test_projection(m3l, projection.country_hour, proj_country_hour)
        i += 1

    return r

def m3summary_file_test(file_name):
    test_ref = [
        "aa01,br,sjk,2019-03-08,06:17:58,300,38,8,0,0,0",
        "aa05,us,lax,2019-03-08,18:36:45,300,152625,102924,4619,1290,0",
        "aa09,cz,xuy,2019-03-08,01:40:28,300,14639,5320,195,20,0",
        "aa23,cz,xuy,2019-03-08,00:30:19,300,15805,6383,307,18,0",
        "aa01,br,crn,2019-04-16,17:38:56,300,176400,132369,20442,316,0",
        "aa02,us,hnl,2019-04-16,14:10:07,300,915,161,0,0,0",
        "aa19,cz,xuy,2019-04-16,23:57:41,300,16567,7213,277,13,10",
        "aa01,mm,rgn,2019-04-16,09:20:57,300,2738,513,1,0,0",
        "aa04,us,lax,2019-04-16,01:37:14,300,144226,93968,3663,840,86",
        "aa01,us,lax,2019-02-02,19:39:10,300,183100,134508,4955,1363,0",
        "aa01,mx,mty,2019-02-02,13:03:46,300,1137235,1116532,612,1334,0",
        "aa01,cz,xuy,2019-02-02,15:01:24,300,25808,15544,902,31,0"]
    test_pcc = [
        "aa00,br,zzz,2020-01-01,00:00:00,600,176438,132377,20442,316,0",
        "aa00,cz,zzz,2020-01-01,00:00:00,1200,72819,34460,1681,82,10",
        "aa00,mm,zzz,2020-01-01,00:00:00,300,2738,513,1,0,0",
        "aa00,mx,zzz,2020-01-01,00:00:00,300,1137235,1116532,612,1334,0",
        "aa00,us,zzz,2020-01-01,00:00:00,1200,480866,331561,13237,3493,86"]

    msl = m3summary_list()
    ret = msl.load_file(file_name)
    if ret != 0:
        return -1
    if len(msl.summary_list) != len(test_ref):
        print("Got " + str(msl.summary_list) + " in <" + file_name + ">")
        return -1
    i = 0
    while i < len(test_ref):
        if msl.summary_list[i].to_string() != test_ref[i]:
            print("Line[" + str(i) + "]: " + msl.summary_list[i].to_string())
            ret = -1
        i += 1
    if ret == 0:
        pcc = msl.project(projection.country)
        if len(pcc) != len(test_pcc):
            print("Got " + str(len(pcc)) + " in <" + file_name + ">")
            return -1
        i = 0
        while i < len(test_pcc):
            if pcc[i].to_string() != test_pcc[i]:
                print("Pcc Line[" + str(i) + "]: " + pcc[i].to_string())
                ret = -1
            i += 1
    return ret