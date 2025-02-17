# Hodiny na věži

Úkolem je realizovat funkci (ne celý program, pouze funkci), která bude počítat, kolikrát budou zvonit zvony na věži v zadaném časovém intervalu.

Předpokládáme hodiny na věži, které dokáží zvonit na zvony a tím odbíjet čas. Hodiny jsou vybavené dvojicí zvonů:

zvon #1, který odbíjí minuty. Zvoní vždy v násobcích 15 minut, zvoní 1x až 4x (XX:00 - 4x, XX:15 - 1x, XX:30 - 2x a XX:45 - 3x).
zvon #2, který odbíjí hodiny, zvoní tolikrát, kolik ukazuje hodinová ručička. Tedy v půlnoci 12x, v 1:00 1x, ve 2:00 2x, ..., ve 12:00 12x, v 13:00 1x, ve 14:00 2x, ...,
v neděli je odbíjení po celý den vypnuté. Tedy naposledy se zvoní v sobotu v 23:45 a pak až v pondělí v 00:00.
Naše funkce dostane parametrem dva časové údaje - počátek a konec časového intervalu. Počátek i konec je dán rokem, měsícem, dnem, hodinou a minutou. Funkce spočítá, kolikrát hodiny v tomto intervalu odbijí na jednom a na druhém zvonu. Pro výpočet uvažujeme uzavřený interval, tedy pokud se odbíjí na začátku/konci zadaného intervalu, do výsledku zahrneme i tato odbíjení.

**Požadovaná funkce má rozhraní:**

int bells ( int y1, int m1, int d1, int h1, int i1,
           int y2, int m2, int d2, int h2, int i2, 
           long long int * b1, long long int * b2 )\
y1, m1, d1, h1, i1\
jsou vstupní parametry, které představují rok, měsíc, den, hodinu a minutu počátku intervalu,\
y2, m2, d2, h2, i2\
jsou vstupní parametry, které představují rok, měsíc, den, hodinu a minutu konce intervalu,\
b1\
je výstupní parametr, do kterého funkce uloží vypočtený počet odbití zvonu #1. Parametr bude funkce nastavovat pouze pokud jsou zadané správné vstupní parametry. Pokud jsou zadané nesprávné vstupy, nelze hodnotu určit. V takovém případě funkce signalizuje neúspěch a ponechá výstupní parametr beze změn.\
b2\
je výstupní parametr, do kterého funkce uloží vypočtený počet odbití zvonu #2. Parametr bude funkce nastavovat pouze pokud jsou zadané správné vstupní parametry. Pokud jsou zadané nesprávné vstupy, nelze hodnotu určit. V takovém případě funkce signalizuje neúspěch a ponechá výstupní parametr beze změn.\
návratová hodnota funkce\
bude nastavena na hodnotu 1 pro úspěch (správné vstupní parametry) nebo 0 pro neúspěch (nesprávné vstupní parametry).\


Pokud jsou zadané nesprávné vstupní parametry, je potřeba vrátit hodnotu 0 (neúspěch). Správné hodnoty vstupních parametrů musí splňovat:

 - rok je větší roven 1600,
 - měsíc je platný (1 až 12),
 - den je platný (1 až počet dní v měsíci),
 - hodina je platná (0 až 23),
 - minuta je platná (0 až 59),
 - zadaný okamžik počátku intervalu nenastane až po zadaném okamžiku konce intervalu.

 - 
Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce bells. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z bells volané. Funkce bude volaná z testovacího prostředí, je proto důležité přesně dodržet zadané rozhraní funkce. Za základ pro implementaci použijte kód z ukázky níže. V kódu chybí vyplnit funkci bells (a případné další podpůrné funkce). Ukázka obsahuje testovací funkci main, uvedené hodnoty jsou použité při základním testu. Všimněte si, že vkládání hlavičkových souborů a funkce main jsou zabalené v bloku podmíněného překladu (#ifdef/#endif). Prosím, ponechte bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně spouštět a testovat. Při kompilaci na Progtestu funkce main a vkládání hlavičkových souborů "zmizí", tedy nebude kolidovat s hlavičkovými soubory a funkcí main testovacího prostředí.

Při výpočtu času uvažujeme Gregoriánský kalendář. Tedy měsíce mají vždy 30 nebo vždy 31 dní, výjimkou je únor, který má 28 dní (nepřestupný rok) nebo 29 dní (přestupný rok). Podle Gregoriánského kalendáře platí:

 - roky nejsou přestupné,
 - s výjimkou let dělitelných 4, které jsou přestupné,
 - s výjimkou let dělitelných 100, které nejsou přestupné,
 - s výjimkou let dělitelných 400, které jsou přestupné,
 - s výjimkou let dělitelných 4000, které nejsou přestupné. Toto pravidlo zatím ještě nikdy neuplatnilo a není zatím oficiálně přijaté. Je to jeden z uvažovaných návrhů, který by Gregoriánský kalendář přiblížil skutečnosti. V naší implementaci jej budeme uvažovat.
 - Tedy roky 1901, 1902, 1903, 1905, ... jsou nepřestupné (pravidlo 1), roky 1904, 1908, ..., 1996, 2004, ... jsou přestupné (pravidlo 2), roky 1700, 1800, 1900, 2100, ... nejsou přestupné (pravidlo 3), roky 1600, 2000, 2400, ..., 3600, 4400, ... jsou přestupné (pravidlo 4) a roky 4000, 8000, ... nejsou přestupné (pravidlo 5).

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Časové limity jsou nastavené tak, aby rozumná implementace naivního algoritmu prošla všemi povinnými testy. Řešení fungující v povinných testech může získat nominálních 100% bodů. Bonusové testy vyžadují časově efektivní výpočet i pro velké intervaly (vysoké roky hodně převyšující 4000).

Ukázku použití naleznete v přiloženém souboru.:

## Nápověda:
Zkopírujte si ukázku z přiloženého archivu a použijte ji jako základ Vašeho řešení.
Do funkce main si můžete doplnit i další Vaše testy, případně ji můžete libovolně změnit. Důležité je zachovat podmíněný překlad.
S pěticí hodnot (rok, měsíc, den, hodina, minuta) se špatně pracuje (například při porovnávání). Je lepší si tyto hodnoty převést na nějakou jinou reprezentaci, ideálně aby vzniklo pouze jedno číslo.
V programu musíte mnoho výpočtů dělat 2x - pro počátek a konec intervalu. Je dobrý nápad vytvořit si pomocné funkce, které 2x zavoláte.
V povinných testech jsou zadávané roky nepřevyšující rok 4000.
Základní řešení, které prochází veškeré okamžiky, kdy se odbíjí, je velmi pomalé a neprojde časovými limity. Není ale potřeba testovat každé odbíjení zvlášť. Vyplatí se např. předpočítat si odbíjení za jeden celý den a iterovat po dnech, případně po delších časových úsecích.
Pro velké intervaly (bonusový test) je počet odbití obrovský. Rozsah datového typu int nepostačuje. Proto má funkce parametrem long long int, který již stačí.
V přiloženém ukázkovém zdrojovém souboru je vidět seznam dostupných hlavičkových souborů. Jiné hlavičkové soubory nejsou k dispozici a ani je nejde pomocí #include dodatečně vložit. Všimněte si, že není k dispozici hlavičkový soubor time.h.
