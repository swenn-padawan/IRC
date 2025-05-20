### Notes Normes IRC
*source: https://www.rfcreader.com/#rfc2812* 
    ps: chaque reference a des pages/section parle de ce lien ^
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
 
##### 2.3.1 Format in ABNF
(ABNF est une maniere de decrire une grammaire synthaxique)
Je vais pas ecrire toutes la liste sonc elle est page 7 (du lien)

#### 2.4 Numeric Replies
La plupart des messages envoye au serveur generent une reponse.
La plus commune est la reponse numerique, utilisees a la fois pour les erreurs et en temps normals.
La reponse numerique DOIT etre envoye en un message:
le prefix de l'envoyeur, les 3 digits, et la distination.
Une reponse numerique n'est pas autorisee si elle vient d'un client
Pour resume une reponse numerique est comme un message normal mais avec des digits a la place d'un mot

### 3 Message Details
Toutes les commandes decrites dans cette section DOIVENT etre implementees.
Quand l'erreur ERR_NOSUCHSERVER est retourner ca veut dire que la destination n'a pas pu etre trouver.
Le serveur NE DOIT PAS envoyer d'autres reponses apres cette erreur pour cette commande.
Exemple: le client envoie:
    WHOIS autre.serveur.net swenn
si le serveur IRC ne connait pas autre.serveur.net
le serveur envoie:
    :ton.serveur.net 402 swenn autre.serveur.net :No such server

Meme si on gere pas la communication entre serveur, le client peut tenter quand meme.

Si plusieurs parametres sont present, chaque parametres doivent etre verifies et chaque erreurs doit etre specifies:
Je cite: "If multiple parameters is presented, then each MUST be checked for
   validity and appropriate responses MUST be sent back to the client.
   In the case of incorrect messages which use parameter lists with
   comma as an item separator, a reply MUST be sent for each item."

#### 3.1 Connection Registration
Une commande PASS n'est pas obligatoire pour que la connection du client soit enregistree,
mais elle doit etre precedee des commandes NICK/USER.
L'ordre conseille des commandes pour la connection d'un user est la suivante:
                            1. Pass message
           2. Nick message                  2. Service message
           3. User message

Si la commande reussi, le user recevra un RPL_WELCOME message indiquant que la connction a bien eu lieu et est connu de tout le serveur IRC.
Le message doit contenir le nom sous lequel le user s'est identifier

Les sous chapitres qui suivent dans la doc sont faciles a lire, pa sla peine de les reecrire: (section 3.1.1 ou page10)

#### Channel Operations
Toutes ces commandes doivent informes le user si la commande a produit une erreur, si elle a ete accordee, ou juste refusee.
Precision: Une erreur peut etre synthaxique ou technique (une fonction qui foire genre send())
    tandis que le refus de la commande vient des permissions (join un channel prive sans invitation, kick alors que non operateur, etc..)

Dans cette section il est mention non implicite d'une notion essentielle pour que le client (Hexchat) puisse fonctionner, l'echo de l'action.
Exemple:    Le client envoie JOIN #salon
            Le serveur renvoie: :swenn!~user@host JOIN :#salon
Et si la commande du client (swenn) prouit une erreur, le serveur ne renvoit pas l'action avec le prefixe, il envoie simplement un message d'erreur ou de refus,
et dans ce cas la le prefixe est le serveur est pas le user.

Je n'ecrirais pas tout les codes d'erreurs de chaque commandes, ils sont disponibles a partir de la page16

##### JOIN message




