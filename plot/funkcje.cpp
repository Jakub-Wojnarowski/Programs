#include <iostream>
#include <cmath>

using namespace std;


void plot(double (*function)(double), double x1, double x2) //rysujemy wykres funkcji pomi�dzy punktami x1 i x2
{
	int d = 10;  //definiujemu rozdzielczo�� (warto�ci x i y b�da skaka�y co 1/d czyli co 0.1 , np. x = {1.1, 1.2, 1.3, 1.4, ...})

	while ((int)(x1 * d) > 10 * d || (int)(x1 * d) < -10 * d || (int)(x2 * d) > 10 * d || (int)(x2 * d) < -10 * d) //x1 i x2 musz� spe�nia� te warunki, �eby wykres nie by� za du�y
	{                                                                                                              //przez ca�y program u�ywamy rzutowania z double na int �eby m�w dok�adnie por�wnywa� warto�ci.
		cout << "zle wartosci x1 i x2\n Wpisz poprawne warto�ci(x1 i x2 >= -10 , x1 i x2 <= 10)" << endl;          //rozdzielczo�� wynosi d (w tym przypadku 10), wiec �eby przy rzutowaniu nie traci� pierwszej liczby po przeciunku
		cin >> x1 >> x2;                                                                                           // mno�ymy nasz� liczbe przed rzutowaniem razy d (w tym przypadku 10)
	}                                                                                                              //u�ywam wszedzie liczby d zamiast po prostu 10, bo w ten spos�b moge zmieni� rozdzielczo�c zmieniaj�c 1 lizcbe na pocz�tku
	if (x1 > x2) swap(x1, x2); // je�li x1 jest wieksze ni� x2 zamieniamy je miejscami                             //skoro mno�ymy przez d jedn� strone nier�wno�ci to musimy te� pomno�y� drug�

	int size = (int)( (x2 - x1 + 0.05) * d ) + 1;  //definiujemy rozmiar tablic (odleg�o�� mi�dzy x1 i x2 razy rozdzielczo��, bo skaczemy co 1/d) 
										  //na ko�cu +1 poniewa� jakby�my mieli x1 = 1 i x2 = 2 to rozmaiar by� by r�wny 10 warto�ci x by�y by r�wne {1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9}
										  //warto�ci x by�y by r�wne {1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9} (10 warto�ci), a chcemy doj�� do 2, czyli potrzebujemy dodatkowego pola
										// +0.05 jest t�d �e cpp zawsze zaokr�gla w d� jak by�my mieli przypadek �e x1 = 2.78, a x2 = 1.31 dostaliby�my (2.78 - 1.31)*10=1.47*10=14.7 i zaokr�gla sie do 14   
										// a chcemy mie� warto�ci od 1.3 do 2.8 w��cznie, czyli (2.8 - 1.3)*10=1.5*10=15 warto�ci. Po dodaniu 0.05 mamy 1.52*10=15, czyli tyle ile ma by�	

	double* x = new double[size]; //tablica przechowuj�ca warto�ci x
	double* y = new double[size]; //tablica przchowuj�ca warto�ci y

	for (int i = 0; i < size; i++) //wype�niamy tablice
	{
		*(x + i) = x1 + i * (1 / (double)d); //pierwsza warto�� to x1 i ka�da kolejna jest wi�ksza od porzedniej o 0.1 a� do x2
		*(y + i) = function(*(x + i));
		if( (int)(*(y + i)*d) > 0 ) *(y + i) += 0.05;                            //do ka�dego y dodajemy 0.05, poniewa� cpp normalnie zaokr�gla tylko w d�, a my chcemy �eby do 0.05 zaokr�gla� w d�, a od 0.05 w g�re
		else if ((int)(*(y + i) * d) < 0) *(y + i) -= 0.05;                           //przyk�ad : mamy y = 0.96 ,cpp zaokr�gli do 0.9, a my chcemy tu mie� 1. Jak dodamy 0.05 bedziemy mie� 1.01 i cpp zaokr�gli do 1
		if ( (int)(*(x + i) * d) > 0 ) *(x + i) += 0.05;                           // jak bedziemy mie� y = 0.94 i dodamy do niego 0.05 to bedziemy mie� 0.99 i cpp wzi�� bedzie zaokr�gla� w d�, czyli tak jak ma by�
		else if ( (int)(*(x + i) * d) < 0 ) *(x + i) -= 0.05;                            // dla y mniejszego od zera musimy odj�� 0.05 poniewa� y = -0.96 jest zaokr�glane do 0. Jak dodamy 0.05 to mamy -0.91, wci�� do 0
	}									                             // dopiero jak odejmiemy dostajemy -1.01 czyli zaokr�gla sie do -1
										                             // to samo robimy z x, ale po przypisaniu warto�ci do y, �eby ta zmiana nie wp�ywa�a na y w nieprzewidywalny spos�b
	                                                   

	double ymax = -10; //szukamy warto�ci ymax i ymin (chcemy �eby ymax <= 10 i ymin >= - 10, �eby wykres nie by� za du�y)
	double ymin = 10;  // na pocz�tku ustalamy ymax na najmniejsz� mo�liw� warto��, a ymin na najwi�ksz�, �eby te warto�ci na pewno zosta�y zmienione w nast�pnej p�tli
					  //gdyby�my ustalili oba na 0 to w funkcji kt�ra mia�aby same warto�ci ujemne nie znale�liby�my ymax. poniewa� �adna jej warto�� nie by�aby wi�ksza od 0 i by go nie nadpisa�a

	for(int i = 0; i < size; i++)
	{
		if (*(y + i) > ymax && *(y + i) <= 10) ymax = *(y + i);
		if (*(y + i) < ymin && *(y + i) >= -10) ymin = *(y + i);
	}

	//Tu sie zaczyna wypisywanie wykresu (to jest mniej istotne, ale napisa�em bo chcia�em narysowa� wykres w konsoli)


	int x_axis_size = size;  //definiujemy rozmiary osi, rozmiar osi x jest r�wny rozmarowi tablic z warto�ciami
	int y_axis_size;
	if (ymax * ymin >= 0) y_axis_size = (int)((ymax - ymin + 0.05) * d) + 1; //rozmiar osi x to odleg�o�� mi�dzy ymin i ymax razy rozdzielczo��(skaczemy co 0.1), +1 z tego samego powodu co na pocz�tku, 0.05 r�wnie�
	else y_axis_size = (int)((ymax - ymin - 0.05) * d) + 1; // kiedy znaki ymax i ymin s� r�ne to odejmujemy 0.05, poniewa� na pocz�tku dodali�my do ka�dej dodatniej warto�ci y 0.05, a od ka�dej ujemnej odjeli�my 0.05
	                                                        // kiedy znaki s� takie same to przy r�nicy (ymax - ymin) to co dodali�my(odjeli�my) sie znosi (0.5 - 0.5 = 0, -0.5 - -0.5 = 0)
															// natomiast kiedy znaki s� r�ne mamy(0.5 - -0.5 = 1), wi�c �eby wnicy by� zwi�kszony o 0.5, to musimy je nie doda� tylko odj�� 
	/*
	for (int i = 0; i < size; i++)
		cout << *(x + i) << "     " << *(y + i) << endl;    //to jest niewa�ne, u�ywa�em tego do debugowania
	cout << endl << endl;
	*/
	
	for (int i = 0; i < y_axis_size; i++) //wypisujemy poziome linijki od g�ry
	{
		double y_wartosc = ymax - i * (1 / (double)d); //zaczynamy iterowa� od ymax i idziemy w d� co 0.1 do ymin. Przpisujemy to do osobnej zmiennej bo jest d�ugie i cz�sto bedziemy tego u�ywa� i w ten spos�b kod jest bardziej przejrzysty
		
		if ((int)(y_wartosc * d) == 0)   // liczby dodatnie s� zwi�kszone o 0.05, a ujemne zmniejszone o 0.05, natomiast my iteruj�c od ymax co 0.1 w d� wi�c je�li ymax > 0 i ymax < 0 to w momencie mini�cia 0 przez y_wartosc wci�� bedziemy mieli warto�ci zwi�kszone o 0.05
			ymax -= 0.1;                  //poniewa� ymax by�o zwi�kszone o 0.05. Warto�ci ujemne musz� by� zmniejszone 0.05 wiec w momencie mijania 0 zmniejszamy ymax o 0.1.
		//we wzorze na y_wartosc jest ymax (y_wartosc = ymax - i * (1 / (double)d)), wi�c jak zmniejszymy o 0.1 ymax to zmniejszymy te� y_wartosc, co prawda stracimy informacje o maksymalnej warto�ci funkcji, ale nie jest ona nam ju� potrzebna

		if ((int)(y_wartosc)*d == (int)(y_wartosc * d) && y_wartosc >= 0) // chcemy wypisa� na osiach tylko liczby ca�kowite. Warunek ten dzia�a w ten spos�b, �e np. y_wartosc r�wne 6.6, dla tej warto�ci warunek bedzie wygl�da� w nast�puj�cy spos�b :
		{                                                                   // (int)(6.6)*10 == (int)(6.6*10)    6*10 == (int)(66)  60 == 66 warunek nie jest spe�niony, natomiast dla 6 mamy (int)(6)*10 == (int)(6*10)   6*10 == (int)(60)    60 == 60 warunek spe�niony
			if ((int)y_wartosc == 10) cout << " " << (int)y_wartosc << '|'; //bedzie on spe�niony dla ka�dej liczby ca�kowitej i nie spe�niony dla ka�dej liczby nieca�kowitej
			else cout << "  " << (int)y_wartosc << '|';
		}                                                                     // warunki na y_wartosc wieksze lub mniejsze od zera s� po to �eby o� by�a r�wno wyspacjowana. Za wyrysowanie osi odpowiada znak '|' i w ka�dej linii musi by� przed nim tyle samo znak�w
		else if ((int)(y_wartosc)*d == (int)(y_wartosc * d) && y_wartosc < 0)// najwi�ksz� liczbe znak�w ma liczba -10 (a� 3), czyli ustalamy �e przed znakiem osi musz� by� 3 znaki. 10 ma 2 znaki wi�c musimy przed nim da� 1 spacje 
		{                                                                         // liczby od -1 do -9 maj� te� 2 znaki wi�c te� dajemy przed nie 1 spacje. Liczby od zera do 9 maj� 1 znak, wi�c dajemy przed nie 2 spacje
			if ((int)y_wartosc == 10) cout << (int)y_wartosc << '|';            // liczb nieca�kowitych nie wypisujemy, wi�c zamiast nich 3 spacje
			else cout << " " << (int)y_wartosc << '|';                          //przy wypisywaniu rzutujemy na int �eby nie wy�wietla�o warto�ci na dalszych miejscach po przecinku
		}
		else
			cout << "   |";
	   

		for (int j = 0; j < size; j++)  //teraz por�wnujemy warto�� y w linii kt�r� aktualnie wypisujemy(y_wartosc) z ka�d� warto�ci� y zapisan� w tablicy y po kolei. Warto�ci w tej tablicy s� u�o�one po kolei od warto�ci dla najmniejszego x do najwi�kszego x, czyli zgodnie z osi� x
		{                               //wiec iterujemy po niej od pocz�tku do ko�ca i sprawdzamy czy jej warto�ci s� r�wne y_wartosc. Je�li dana warto�� jest jej r�wna wypisujemy kropke, je�li nie wypisujemy spacje
			if ((int)(y_wartosc * d) == (int)(*(y + j) * d)) cout << '.'; // np. dla sinusa  dajemy przedzia� x1 = 0, x2 = 6.5. ymax = 1, a ymin = -1. Pierwszy element tablicy y to y(x1), czyli y(0) = 0. Wypisuj�c linie wypisujemy je od najwi�kszego y czyli ymax = 1. 0 != 1 wiec wypisze sie spacja
			else cout << ' ';                                              // dla pierwszej linii kropka wypisze sie dopiero dla y(pi/2), ok. y(1.6). poniewa� y(1.6) == y_wartosc    1==1  (w rzeczywisto�ci wypisze sie w otoczeniu tego punktu kilka kropek ko�o siebie poniewa� zaokr�glamy z kod��dno�cia do 0.1) 
		}                                                                  // dla kolejnej linii kropka wypisze sie troszeczke wcze�niej, ale r�wnie� troszeczke p�niej, kiedy sinus minie maximum i zacznie opada�
		cout << endl;  //tu ko�czy sie linia                               // dla ka�dej kolejnej linii kropka bedzie wypisywa�a sie troszke wcze�niej i troszke p�niej wzgl�dem punktu y(1.6) ni� w poprzedniej linii, a� w ko�cu w linii w kt�rej y_wartosc = 0 wypisze sie na pierwszym miejscu, czyli dla y(0)
	}//przechodzimy do nast�pnej i zaczynamy kolejn� iteracje p�tli    // po wypisaniu w ten spos�b wszystkich linii kropki utworz� kszta�t sinusa
	

	cout << "----";           //osie x i y nie b�d� si� przecina�y w punkcie (0,0), tylko o� x bedzie na samym dole. Znakiem osi x bedzie '-'. Na pocz�tku wypisujemy cztery znaki osi (s� te te odpowiadaj�ce trzem znak� warto�ci i znakowi osi y w poprzednich liniach)
	for (int i = 0; i < size; i++) //nast�pnie dla ka�dej kom�rki w tablicy x wypisujemy jeden znak osi.
		cout << '-';
	cout << endl;    //przechodzimy do nast�pnej linii i w odpowiednich miejscach wypisujemy warto�ci ca�kowite osi x

	if ((int)(x1 * d) > 0) x1 += 0.05;                //wcze�niej zmodyfikowali�my warto�ci wszystkich x o 0.05 w jedn� albo drug� strone, ale nie zrobili�my tego dla x1 i x2, kt�re by�y przekazane do funkcji jako parametry
	else if ((int)(x1 * d) < 0) x1 -= 0.05;           // bedziemy teraz iterowa� po p�tli przy u�yciu x1, wi�c musimy uwzgl�dni� t� modyfikacje o 0.05, �eby by�o r�wne najmniejszej warto�ci w tablicy. Z x2 nic nie robimy bo nie bedziemy go u�ywa�


	cout << "    ";  //na pocz�tku 4 spacje (z tego samego powodu co wcze�niej 4 my�lniki)
	for (int i = 0; i < size; i++)                                             //Najpierw musimy wypisa� dodatkow� linie wypisujac� znaki odpowiednich liczb ca�kowitych. Nie mo�emy tego zrobi� w tej samej linii co same liczby, poniewa� np. liczba -3 ma 2 znaki a tylko jedno pole na wypisanie jej
	{

		double x_wartosc = x1 + i * (1 / (double)d);                    // iterujemy od x1 co 0.1 do x2

		if ((int)(x_wartosc * d) == 0)                                    //robimy to samo co przy przekraczaniu 0 na osi y tylko tym razem przekraczmy je od strony ujemnej na dodatni�, wi�c dodajemy 0.01 zamiast je odejmowa�
			x1 += 0.1;

 
		if ((int)(x_wartosc) * d == (int)(x_wartosc * d) && (int)(x_wartosc * d) < 0)  //warunek taki sam jak przy wypisywaniu warto�ci ca�kowitych osi y i dodatkowo sprawdzamy czy ta liczba ca�kowita jest mniejsza od 0
			cout << "-";                                                     // dla liczb ujemnych wypiszemy w tej linii '-'                                             
		else if ((int)(x_wartosc) * d == (int)(x_wartosc * d) && (int)(x_wartosc * d) > 0) // teraz dla wi�kszych od 0
			cout << "+";                                                          // i wypisujemy dla nich plus, bo puste pole by g�upio wygl�da�o
		else cout << " ";                                                       //dla liczb nieca�kowitych wypisujemy spacje

	}

	if(x1 * x2 < 0) x1 -= 0.1;             //teraz je�li w poprzedniej p�tli dodali�my do x1 0.01 to musimy je z powrotem odj�� poniewa� bedziemy z niego korzysta� w ten sam spos�b
	                                       // w p�tli 0.01 zosta�o dodane w momencie przej�cia przez 0, a to stanie sie tylko wtedy kiedy x1 i x2 s� przeciwnych znak�w

	cout << endl; // koniec tej linii, teraz wypisujemy warto�ci bezwzgl�dne liczb ca�kowitych

	if ((int)(x1) == -10) cout << "   ";                // je�li x1 = -10 wypisujemy tylko 3 spacje zamiast 4, poniewa� liczba 10 ma wi�cej znak�w i potrzebujemy na ni� dodatkowego pola. Na szcz�scie jest najmniejsz� mo�liw� warto�ci� i zawsze bedzie na lewym skraju wi�c mo�emy sobie ukra�� 1 pole sprzed samego wykresu i zamiast wypisywa� ostatni� spacje przeznaczym je na dodatkowe miejsce dla -10
	else cout << "    ";                               // wi�c mo�emy sobie ukra�� 1 pole sprzed samego wykresu i zamiast wypisywa� ostatni� spacje przeznaczym je na dodatkowe miejsce dla -10
	                                                // liczby x2 = 10 nie musimy uwzgl�dnia� bo ona zawsze bedzie sie znajdowa�a na prawym skraju a za nim i tak s� puste pola kt�rych do niczego nie u�ywamy
	
	for (int i = 0; i < size; i++)
	{
		double x_wartosc = x1 + i * (1 / (double)d);                            // iterujemy od x1 co 0.1 do x2
		if ((int)(x_wartosc * d) == 0)                                              //tu te� trzeba uwzgl�dni� x przechodz�ce przez 0
			x1 += 0.1;

		if ((int)(x_wartosc) * d == (int)(x_wartosc * d) && x_wartosc >= 0)   //warunek por�wnuj�cy taki sam jak porzednio i dodatkowy �e dla liczb dodatnich wypisujemy te liczby
			cout << (int)x_wartosc;                                             //przy wypisywaniu rzutujemy na int �eby nie wy�wietla�o warto�ci na dalszych miejscach po 
		else if ((int)(x_wartosc) * d == (int)(x_wartosc * d) && x_wartosc < 0)
			cout << -(int)x_wartosc;                                          // teraz dla liczb ujemnych i dla nich wypisujemy i te liczby czyli ich warto�ci bezwzgl�dne   
		else
			cout << ' ';                                                        //dla warto�ci niecakowitych wypisujemy spacje
                                                         
	}
	cout << endl;
	
	delete[] x;
	delete[] y;
}

void swap(double* x1, double* x2) //funkcja swap zamienia przez wska�niki warto�ci dw�ch zmiennych
{
	double temp = *x1;
	*x1 = *x2;
	*x2 = temp;
}