var table = {
    "slash" : "…±",
    "jink" : "…¡",
    "peach" : "Ã“",
};

sgs.addTranslationTable(table);

var slash = sgs.addCardClass("slash", "Basic");
var jink = sgs.addCardClass("jink", "Basic");
var peach = sgs.addCardClass("peach", "Basic");

var duel = sgs.addCardClass("duel", "Trick");
var lightning = sgs.addCardClass("lightning", "Trick");
var double_sword = sgs.addCardClass("double_sword", "Equip");
var eight_diagram = sgs.addCardClass("eight_diagram", "Basic");

sgs.addCard("duel", "spade", 1);
sgs.addCard("lightning", "spade", 1);
sgs.addCard("double_sword", "spade", 2);
sgs.addCard("eight_diagram", "diamond", "J");
