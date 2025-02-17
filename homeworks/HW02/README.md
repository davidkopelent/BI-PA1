# Body v rovině

Úkolem je realizovat program, který pro trojici zadaných bodů ve 2D rovině rozhodne, zda leží na společné přímce.

Vstupem programu jsou X a Y souřadnice trojice bodů ve 2D rovině. Souřadnice jsou zadané jako dvě desetinná čísla, prvé číslo reprezentuje složku X a druhé číslo složku Y.

Program analyzuje vzájemnou polohu zadaných bodů a rozhodne, který ze tří závěrů je platný:

dva nebo všechny tři zadané body splývají,
zadané 3 body jsou navzájem různé a neleží na jedné přímce nebo
zadané 3 body jsou navzájem různé a leží na jedné přímce (pak program navíc určí prostření bod).
Formát výstupu je zřejmý z ukázek níže.
Program musí kontrolovat správnost zadání vstupních dat. Pokud je na vstupu zadaná nesprávná hodnota (nečíselná), pak program detekuje chybu, zobrazí na standardním výstupu chybové hlášení podle ukázky a ukončí se.

## Ukázky práce programu:
Bod A:\
1 2\
Bod B:\
3 4\
Bod C:\
5 6\
Body lezi na jedne primce.\
Prostredni je bod B.

## Nápověda:
Ukázkové běhy zachycují očekávané výpisy Vašeho programu (tučné písmo) a vstupy zadané uživatelem (základní písmo). Zvýraznění tučným písmem je použité pouze zde na stránce zadání, aby byl výpis lépe čitelný. Váš program má za úkol pouze zobrazit text bez zvýrazňování (bez HTML markupu).
Znak odřádkování (\n) je i za poslední řádkou výstupu (i za případným chybovým hlášením).
Při řešení se snažte omezit celkový počet podmínek. S výhodou lze využít vektorové algebry.
