#include <iostream>
#include <cmath>

using namespace std;


void plot(double (*function)(double), double x1, double x2) //rysujemy wykres funkcji pomiêdzy punktami x1 i x2
{
	int d = 10;  //definiujemu rozdzielczoœæ (wartoœci x i y bêda skaka³y co 1/d czyli co 0.1 , np. x = {1.1, 1.2, 1.3, 1.4, ...})

	while ((int)(x1 * d) > 10 * d || (int)(x1 * d) < -10 * d || (int)(x2 * d) > 10 * d || (int)(x2 * d) < -10 * d) //x1 i x2 musz¹ spe³niaæ te warunki, ¿eby wykres nie by³ za du¿y
	{                                                                                                              //przez ca³y program u¿ywamy rzutowania z double na int ¿eby mów dok³adnie porównywaæ wartoœci.
		cout << "zle wartosci x1 i x2\n Wpisz poprawne wartoœci(x1 i x2 >= -10 , x1 i x2 <= 10)" << endl;          //rozdzielczoœæ wynosi d (w tym przypadku 10), wiec ¿eby przy rzutowaniu nie traciæ pierwszej liczby po przeciunku
		cin >> x1 >> x2;                                                                                           // mno¿ymy nasz¹ liczbe przed rzutowaniem razy d (w tym przypadku 10)
	}                                                                                                              //u¿ywam wszedzie liczby d zamiast po prostu 10, bo w ten sposób moge zmieniæ rozdzielczoœc zmieniaj¹c 1 lizcbe na pocz¹tku
	if (x1 > x2) swap(x1, x2); // jeœli x1 jest wieksze ni¿ x2 zamieniamy je miejscami                             //skoro mno¿ymy przez d jedn¹ strone nierównoœci to musimy te¿ pomno¿yæ drug¹

	int size = (int)( (x2 - x1 + 0.05) * d ) + 1;  //definiujemy rozmiar tablic (odleg³oœæ miêdzy x1 i x2 razy rozdzielczoœæ, bo skaczemy co 1/d) 
										  //na koñcu +1 poniewa¿ jakbyœmy mieli x1 = 1 i x2 = 2 to rozmaiar by³ by równy 10 wartoœci x by³y by równe {1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9}
										  //wartoœci x by³y by równe {1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9} (10 wartoœci), a chcemy dojœæ do 2, czyli potrzebujemy dodatkowego pola
										// +0.05 jest t¹d ¿e cpp zawsze zaokr¹gla w dó³ jak byœmy mieli przypadek ¿e x1 = 2.78, a x2 = 1.31 dostalibyœmy (2.78 - 1.31)*10=1.47*10=14.7 i zaokr¹gla sie do 14   
										// a chcemy mieæ wartoœci od 1.3 do 2.8 w³¹cznie, czyli (2.8 - 1.3)*10=1.5*10=15 wartoœci. Po dodaniu 0.05 mamy 1.52*10=15, czyli tyle ile ma byæ	

	double* x = new double[size]; //tablica przechowuj¹ca wartoœci x
	double* y = new double[size]; //tablica przchowuj¹ca wartoœci y

	for (int i = 0; i < size; i++) //wype³niamy tablice
	{
		*(x + i) = x1 + i * (1 / (double)d); //pierwsza wartoœæ to x1 i ka¿da kolejna jest wiêksza od porzedniej o 0.1 a¿ do x2
		*(y + i) = function(*(x + i));
		if( (int)(*(y + i)*d) > 0 ) *(y + i) += 0.05;                            //do ka¿dego y dodajemy 0.05, poniewa¿ cpp normalnie zaokr¹gla tylko w dó³, a my chcemy ¿eby do 0.05 zaokr¹gla³ w dó³, a od 0.05 w góre
		else if ((int)(*(y + i) * d) < 0) *(y + i) -= 0.05;                           //przyk³ad : mamy y = 0.96 ,cpp zaokr¹gli do 0.9, a my chcemy tu mieæ 1. Jak dodamy 0.05 bedziemy mieæ 1.01 i cpp zaokr¹gli do 1
		if ( (int)(*(x + i) * d) > 0 ) *(x + i) += 0.05;                           // jak bedziemy mieæ y = 0.94 i dodamy do niego 0.05 to bedziemy mieæ 0.99 i cpp wzi¹¿ bedzie zaokr¹gla³ w dó³, czyli tak jak ma byæ
		else if ( (int)(*(x + i) * d) < 0 ) *(x + i) -= 0.05;                            // dla y mniejszego od zera musimy odj¹æ 0.05 poniewa¿ y = -0.96 jest zaokr¹glane do 0. Jak dodamy 0.05 to mamy -0.91, wci¹¿ do 0
	}									                             // dopiero jak odejmiemy dostajemy -1.01 czyli zaokr¹gla sie do -1
										                             // to samo robimy z x, ale po przypisaniu wartoœci do y, ¿eby ta zmiana nie wp³ywa³a na y w nieprzewidywalny sposób
	                                                   

	double ymax = -10; //szukamy wartoœci ymax i ymin (chcemy ¿eby ymax <= 10 i ymin >= - 10, ¿eby wykres nie by³ za du¿y)
	double ymin = 10;  // na pocz¹tku ustalamy ymax na najmniejsz¹ mo¿liw¹ wartoœæ, a ymin na najwiêksz¹, ¿eby te wartoœci na pewno zosta³y zmienione w nastêpnej pêtli
					  //gdybyœmy ustalili oba na 0 to w funkcji która mia³aby same wartoœci ujemne nie znaleŸlibyœmy ymax. poniewa¿ ¿adna jej wartoœæ nie by³aby wiêksza od 0 i by go nie nadpisa³a

	for(int i = 0; i < size; i++)
	{
		if (*(y + i) > ymax && *(y + i) <= 10) ymax = *(y + i);
		if (*(y + i) < ymin && *(y + i) >= -10) ymin = *(y + i);
	}

	//Tu sie zaczyna wypisywanie wykresu (to jest mniej istotne, ale napisa³em bo chcia³em narysowaæ wykres w konsoli)


	int x_axis_size = size;  //definiujemy rozmiary osi, rozmiar osi x jest równy rozmarowi tablic z wartoœciami
	int y_axis_size;
	if (ymax * ymin >= 0) y_axis_size = (int)((ymax - ymin + 0.05) * d) + 1; //rozmiar osi x to odleg³oœæ miêdzy ymin i ymax razy rozdzielczoœæ(skaczemy co 0.1), +1 z tego samego powodu co na pocz¹tku, 0.05 równie¿
	else y_axis_size = (int)((ymax - ymin - 0.05) * d) + 1; // kiedy znaki ymax i ymin s¹ ró¿ne to odejmujemy 0.05, poniewa¿ na pocz¹tku dodaliœmy do ka¿dej dodatniej wartoœci y 0.05, a od ka¿dej ujemnej odjeliœmy 0.05
	                                                        // kiedy znaki s¹ takie same to przy ró¿nicy (ymax - ymin) to co dodaliœmy(odjeliœmy) sie znosi (0.5 - 0.5 = 0, -0.5 - -0.5 = 0)
															// natomiast kiedy znaki s¹ ró¿ne mamy(0.5 - -0.5 = 1), wiêc ¿eby wnicy by³ zwiêkszony o 0.5, to musimy je nie dodaæ tylko odj¹æ 
	/*
	for (int i = 0; i < size; i++)
		cout << *(x + i) << "     " << *(y + i) << endl;    //to jest niewa¿ne, u¿ywa³em tego do debugowania
	cout << endl << endl;
	*/
	
	for (int i = 0; i < y_axis_size; i++) //wypisujemy poziome linijki od góry
	{
		double y_wartosc = ymax - i * (1 / (double)d); //zaczynamy iterowaæ od ymax i idziemy w dó³ co 0.1 do ymin. Przpisujemy to do osobnej zmiennej bo jest d³ugie i czêsto bedziemy tego u¿ywaæ i w ten sposób kod jest bardziej przejrzysty
		
		if ((int)(y_wartosc * d) == 0)   // liczby dodatnie s¹ zwiêkszone o 0.05, a ujemne zmniejszone o 0.05, natomiast my iteruj¹c od ymax co 0.1 w dó³ wiêc jeœli ymax > 0 i ymax < 0 to w momencie miniêcia 0 przez y_wartosc wci¹¿ bedziemy mieli wartoœci zwiêkszone o 0.05
			ymax -= 0.1;                  //poniewa¿ ymax by³o zwiêkszone o 0.05. Wartoœci ujemne musz¹ byæ zmniejszone 0.05 wiec w momencie mijania 0 zmniejszamy ymax o 0.1.
		//we wzorze na y_wartosc jest ymax (y_wartosc = ymax - i * (1 / (double)d)), wiêc jak zmniejszymy o 0.1 ymax to zmniejszymy te¿ y_wartosc, co prawda stracimy informacje o maksymalnej wartoœci funkcji, ale nie jest ona nam ju¿ potrzebna

		if ((int)(y_wartosc)*d == (int)(y_wartosc * d) && y_wartosc >= 0) // chcemy wypisaæ na osiach tylko liczby ca³kowite. Warunek ten dzia³a w ten sposób, ¿e np. y_wartosc równe 6.6, dla tej wartoœci warunek bedzie wygl¹da³ w nastêpuj¹cy sposób :
		{                                                                   // (int)(6.6)*10 == (int)(6.6*10)    6*10 == (int)(66)  60 == 66 warunek nie jest spe³niony, natomiast dla 6 mamy (int)(6)*10 == (int)(6*10)   6*10 == (int)(60)    60 == 60 warunek spe³niony
			if ((int)y_wartosc == 10) cout << " " << (int)y_wartosc << '|'; //bedzie on spe³niony dla ka¿dej liczby ca³kowitej i nie spe³niony dla ka¿dej liczby nieca³kowitej
			else cout << "  " << (int)y_wartosc << '|';
		}                                                                     // warunki na y_wartosc wieksze lub mniejsze od zera s¹ po to ¿eby oœ by³a równo wyspacjowana. Za wyrysowanie osi odpowiada znak '|' i w ka¿dej linii musi byæ przed nim tyle samo znaków
		else if ((int)(y_wartosc)*d == (int)(y_wartosc * d) && y_wartosc < 0)// najwiêksz¹ liczbe znaków ma liczba -10 (a¿ 3), czyli ustalamy ¿e przed znakiem osi musz¹ byæ 3 znaki. 10 ma 2 znaki wiêc musimy przed nim daæ 1 spacje 
		{                                                                         // liczby od -1 do -9 maj¹ te¿ 2 znaki wiêc te¿ dajemy przed nie 1 spacje. Liczby od zera do 9 maj¹ 1 znak, wiêc dajemy przed nie 2 spacje
			if ((int)y_wartosc == 10) cout << (int)y_wartosc << '|';            // liczb nieca³kowitych nie wypisujemy, wiêc zamiast nich 3 spacje
			else cout << " " << (int)y_wartosc << '|';                          //przy wypisywaniu rzutujemy na int ¿eby nie wyœwietla³o wartoœci na dalszych miejscach po przecinku
		}
		else
			cout << "   |";
	   

		for (int j = 0; j < size; j++)  //teraz porównujemy wartoœæ y w linii któr¹ aktualnie wypisujemy(y_wartosc) z ka¿d¹ wartoœci¹ y zapisan¹ w tablicy y po kolei. Wartoœci w tej tablicy s¹ u³o¿one po kolei od wartoœci dla najmniejszego x do najwiêkszego x, czyli zgodnie z osi¹ x
		{                               //wiec iterujemy po niej od pocz¹tku do koñca i sprawdzamy czy jej wartoœci s¹ równe y_wartosc. Jeœli dana wartoœæ jest jej równa wypisujemy kropke, jeœli nie wypisujemy spacje
			if ((int)(y_wartosc * d) == (int)(*(y + j) * d)) cout << '.'; // np. dla sinusa  dajemy przedzia³ x1 = 0, x2 = 6.5. ymax = 1, a ymin = -1. Pierwszy element tablicy y to y(x1), czyli y(0) = 0. Wypisuj¹c linie wypisujemy je od najwiêkszego y czyli ymax = 1. 0 != 1 wiec wypisze sie spacja
			else cout << ' ';                                              // dla pierwszej linii kropka wypisze sie dopiero dla y(pi/2), ok. y(1.6). poniewa¿ y(1.6) == y_wartosc    1==1  (w rzeczywistoœci wypisze sie w otoczeniu tego punktu kilka kropek ko³o siebie poniewa¿ zaokr¹glamy z kod³¹dnoœcia do 0.1) 
		}                                                                  // dla kolejnej linii kropka wypisze sie troszeczke wczeœniej, ale równie¿ troszeczke póŸniej, kiedy sinus minie maximum i zacznie opadaæ
		cout << endl;  //tu koñczy sie linia                               // dla ka¿dej kolejnej linii kropka bedzie wypisywa³a sie troszke wczeœniej i troszke póŸniej wzglêdem punktu y(1.6) ni¿ w poprzedniej linii, a¿ w koñcu w linii w której y_wartosc = 0 wypisze sie na pierwszym miejscu, czyli dla y(0)
	}//przechodzimy do nastêpnej i zaczynamy kolejn¹ iteracje pêtli    // po wypisaniu w ten sposób wszystkich linii kropki utworz¹ kszta³t sinusa
	

	cout << "----";           //osie x i y nie bêd¹ siê przecina³y w punkcie (0,0), tylko oœ x bedzie na samym dole. Znakiem osi x bedzie '-'. Na pocz¹tku wypisujemy cztery znaki osi (s¹ te te odpowiadaj¹ce trzem znak¹ wartoœci i znakowi osi y w poprzednich liniach)
	for (int i = 0; i < size; i++) //nastêpnie dla ka¿dej komórki w tablicy x wypisujemy jeden znak osi.
		cout << '-';
	cout << endl;    //przechodzimy do nastêpnej linii i w odpowiednich miejscach wypisujemy wartoœci ca³kowite osi x

	if ((int)(x1 * d) > 0) x1 += 0.05;                //wczeœniej zmodyfikowaliœmy wartoœci wszystkich x o 0.05 w jedn¹ albo drug¹ strone, ale nie zrobiliœmy tego dla x1 i x2, które by³y przekazane do funkcji jako parametry
	else if ((int)(x1 * d) < 0) x1 -= 0.05;           // bedziemy teraz iterowaæ po pêtli przy u¿yciu x1, wiêc musimy uwzglêdniæ t¹ modyfikacje o 0.05, ¿eby by³o równe najmniejszej wartoœci w tablicy. Z x2 nic nie robimy bo nie bedziemy go u¿ywaæ


	cout << "    ";  //na pocz¹tku 4 spacje (z tego samego powodu co wczeœniej 4 myœlniki)
	for (int i = 0; i < size; i++)                                             //Najpierw musimy wypisaæ dodatkow¹ linie wypisujac¹ znaki odpowiednich liczb ca³kowitych. Nie mo¿emy tego zrobiæ w tej samej linii co same liczby, poniewa¿ np. liczba -3 ma 2 znaki a tylko jedno pole na wypisanie jej
	{

		double x_wartosc = x1 + i * (1 / (double)d);                    // iterujemy od x1 co 0.1 do x2

		if ((int)(x_wartosc * d) == 0)                                    //robimy to samo co przy przekraczaniu 0 na osi y tylko tym razem przekraczmy je od strony ujemnej na dodatni¹, wiêc dodajemy 0.01 zamiast je odejmowaæ
			x1 += 0.1;

 
		if ((int)(x_wartosc) * d == (int)(x_wartosc * d) && (int)(x_wartosc * d) < 0)  //warunek taki sam jak przy wypisywaniu wartoœci ca³kowitych osi y i dodatkowo sprawdzamy czy ta liczba ca³kowita jest mniejsza od 0
			cout << "-";                                                     // dla liczb ujemnych wypiszemy w tej linii '-'                                             
		else if ((int)(x_wartosc) * d == (int)(x_wartosc * d) && (int)(x_wartosc * d) > 0) // teraz dla wiêkszych od 0
			cout << "+";                                                          // i wypisujemy dla nich plus, bo puste pole by g³upio wygl¹da³o
		else cout << " ";                                                       //dla liczb nieca³kowitych wypisujemy spacje

	}

	if(x1 * x2 < 0) x1 -= 0.1;             //teraz jeœli w poprzedniej pêtli dodaliœmy do x1 0.01 to musimy je z powrotem odj¹æ poniewa¿ bedziemy z niego korzystaæ w ten sam sposób
	                                       // w pêtli 0.01 zosta³o dodane w momencie przejœcia przez 0, a to stanie sie tylko wtedy kiedy x1 i x2 s¹ przeciwnych znaków

	cout << endl; // koniec tej linii, teraz wypisujemy wartoœci bezwzglêdne liczb ca³kowitych

	if ((int)(x1) == -10) cout << "   ";                // jeœli x1 = -10 wypisujemy tylko 3 spacje zamiast 4, poniewa¿ liczba 10 ma wiêcej znaków i potrzebujemy na ni¹ dodatkowego pola. Na szczêscie jest najmniejsz¹ mo¿liw¹ wartoœci¹ i zawsze bedzie na lewym skraju wiêc mo¿emy sobie ukraœæ 1 pole sprzed samego wykresu i zamiast wypisywaæ ostatni¹ spacje przeznaczym je na dodatkowe miejsce dla -10
	else cout << "    ";                               // wiêc mo¿emy sobie ukraœæ 1 pole sprzed samego wykresu i zamiast wypisywaæ ostatni¹ spacje przeznaczym je na dodatkowe miejsce dla -10
	                                                // liczby x2 = 10 nie musimy uwzglêdniaæ bo ona zawsze bedzie sie znajdowa³a na prawym skraju a za nim i tak s¹ puste pola których do niczego nie u¿ywamy
	
	for (int i = 0; i < size; i++)
	{
		double x_wartosc = x1 + i * (1 / (double)d);                            // iterujemy od x1 co 0.1 do x2
		if ((int)(x_wartosc * d) == 0)                                              //tu te¿ trzeba uwzglêdniæ x przechodz¹ce przez 0
			x1 += 0.1;

		if ((int)(x_wartosc) * d == (int)(x_wartosc * d) && x_wartosc >= 0)   //warunek porównuj¹cy taki sam jak porzednio i dodatkowy ¿e dla liczb dodatnich wypisujemy te liczby
			cout << (int)x_wartosc;                                             //przy wypisywaniu rzutujemy na int ¿eby nie wyœwietla³o wartoœci na dalszych miejscach po 
		else if ((int)(x_wartosc) * d == (int)(x_wartosc * d) && x_wartosc < 0)
			cout << -(int)x_wartosc;                                          // teraz dla liczb ujemnych i dla nich wypisujemy i te liczby czyli ich wartoœci bezwzglêdne   
		else
			cout << ' ';                                                        //dla wartoœci niecakowitych wypisujemy spacje
                                                         
	}
	cout << endl;
	
	delete[] x;
	delete[] y;
}

void swap(double* x1, double* x2) //funkcja swap zamienia przez wskaŸniki wartoœci dwóch zmiennych
{
	double temp = *x1;
	*x1 = *x2;
	*x2 = temp;
}