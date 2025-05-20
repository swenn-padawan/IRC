### Notes Normes IRC
*source: https://www.rfcreader.com/#rfc2812*

### 1 Labels

#### 1.2.1 Users 

Chaque utilisateur doit avoir un nom unique, et sa taille ne doit pas depasser 9
Je cite un passage de la Norme rfc:
"While the maximum length is limited to nine characters, clients
   SHOULD accept longer strings as they may become used in future
   evolutions of the protocol."
Donc je pense que l'on peut accepter plus de 9 caracteres, mais qu'on affiche/compare que les 9 premiers ?

#### 1.2.1.1 Operators 

Les operators sont en gros les "admins" (aussi appeles les IRCops) du serveur, il peuvent:
Faire toutes les commandes decrites dans le sujet

Donner le status d'operators a un user peut etre consideres comme dangereux

#### 1.3 Channels

Le nom des channels commencent par: '&', '#', '+' ou '!',, et font maximum 50 caracteres
La seule restriction sur le nom est qu'il ne doit pas contenir d'espaces, ni de control G (^G ou 7 en ascii)
Les espaces sont utilises pour separer les commandes.
Un ':' peut etre utilises comme delimiteur pour le mask du channel.
Le nom des channels est case sensitive.
Pour tout ca, Voir la section 2.3.1 du lien plus haut.

### 2 The IRC Client Specification

Je cite: "Because of IRC's Scandinavian origin, the characters {}|^ are
   considered to be the lower case equivalents of the characters []\~,
   respectively. This is a critical issue when determining the
   equivalence of two nicknames or channel names."
Ca veut dire que Swenn[] et Swenn{} sont la meme chose. De meme pour #test| et #test\

#### 2.3 Messages

Chaque messages IRC peut etre decoupes en 3 grosses parties:
- Le prefix (OPTIONNEL) = Voir p.5 du lien plus haut.
- La commandes
- Les parametres de la commande (max 15)
Tout ces caracteres doivent etres separes par un espaces (0x20 en ascii)

La presence d'un prefixe est indique par la presence d'un (':', 0x3b) est DOIT etre le premier characters du message.
Il ne doit pas y avoir d'espaces entre le ':' et le prefix
Les clients ne DOIVENT pas utilises des prefix , le seul prefix valide est le nom associe au client.

La commandes DOIT etre un commande IRC Valide ou une combinaison de 3 digits, exemple: 001 -> binevenue, 433 -> pseudo deja utilise, etc..
Elles sont benefiques pour que Hexchat comprennent ce qu'il se passe. Voir 5.Replies dans le lien plus haut.

Les messages IRC se terminent tous par un CR-LF (Carriage Return-Line Feed) "crlf       =  %x0D %x0A   ; "carriage return" "linefeed""
Ces messages ne DOIVENT pas exceder 512 caracteres
 
#### 2.3.1 Format in ABNF
(ABNF est une maniere de decrire une grammaire synthaxique)
Je vais pas ecrire toutes la liste sonc elle est page 7 (du lien)

### 3 Message Details







