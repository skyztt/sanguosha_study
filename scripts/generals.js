var table = {
    // κ���佫
    "caocao" : "�ܲ�",
    "zhangliao" : "����",
    "guojia" : "����",
    "xiahoudun" : "�ĺ",
    "simayi" : "˾��ܲ",
    "xuchu" : "����",
    "zhenji" : "�缧",

    //����佫
    "liubei" : "����",
    "guanyu" : "����",
    "zhangfei" : "�ŷ�",
    "zhaoyun" : "����",
    "machao" : "��",
    "zhugeliang" : "�����",
    "huangyueying" : "����Ӣ",

    // ����佫
    "sunquan" : "��Ȩ",
    "zhouyu" : "���",
    "lumeng" : "����",
    "luxun" : "½ѷ",
    "ganning" : "����",
    "huanggai" : "�Ƹ�",
    "daqiao" : "����",
    "sunshangxiang" : "������",

    // Ⱥ��
    "lubu" : "����",
    "huatuo" : "��٢",
    "diaochan" : "����",

    // ����
    "wei" : "κ",
    "shu" : "��",
    "wu" : "��",
    "qun" : "Ⱥ",

    // ����
    "jianxiong" : "����",
    "hujia" : "����",
    "tuxi" : "ͻϮ",
    "tiandu" : "���",
    "yiji" : "�ż�",
    "ganglie" : "����",

    "rende" : "�ʵ�",
    "jijiang" : "����",
    "wusheng" : "��ʥ",
    "paoxiao" : "����",
    "longdan" : "����",
    "tieji" : "����",
    "mashu" : "����",
};

sgs.addTranslationTable(table);

// general's skills
//var jianxiong = sgs.addSkill("jianxiong");
//var hujia = sgs.addSkill("hujia");

var caocao = sgs.addGeneral("caocao", "wei");
//caocao.skills = [ jianxiong, hujia ];

var zhangliao = sgs.addGeneral("zhangliao", "wei");
var guojia = sgs.addGeneral("guojia", "wei", 3);
var xiahoudun = sgs.addGeneral("xiahoudun", "wei");
var simayi = sgs.addGeneral("simayi", "wei", 3);
var xuchu = sgs.addGeneral("xuchu", "wei");
var zhenji = sgs.addGeneral("zhenji", "wei", 3, false);

var liubei = sgs.addGeneral("liubei", "shu");
var guanyu = sgs.addGeneral("guanyu", "shu");
var zhangfei = sgs.addGeneral("zhangfei", "shu");
var zhaoyun = sgs.addGeneral("zhaoyun", "shu");
var machao = sgs.addGeneral("machao", "shu");
var zhugeliang = sgs.addGeneral("zhugeliang", "shu", 3);
var huangyueying = sgs.addGeneral("huangyueying", "shu", 3, false);

var sunquan = sgs.addGeneral("sunquan", "wu");
var zhouyu = sgs.addGeneral("zhouyu", "wu", 3);
var lumeng = sgs.addGeneral("lumeng", "wu");
var luxun = sgs.addGeneral("luxun", "wu", 3);
var huanggai = sgs.addGeneral("hunggai", "wu");
var ganning = sgs.addGeneral("ganning", "wu");
var daqiao = sgs.addGeneral("daqiao", "wu", 3, false);
var sunshangxiang = sgs.addGeneral("sunshangxiang", "wu", 3, false);


