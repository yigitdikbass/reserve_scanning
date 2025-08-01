#include <graphics.h>
#include <curl/curl.h>
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctype.h>
#include <math.h>
#include <algorithm>
// Belirli bir noktanýn çokgenin içinde olup olmadýðýný kontrol eden fonksiyon
int sayac=0;
int pikselKontrol(int x, int y, int numPoints, int* points) {
    int i, j;
    int c = 0;
    for (i = 0, j = numPoints-1; i < numPoints; j = i++) {
        if (((points[2 * i + 1] > y) != (points[2 * j + 1] > y)) &&
            (x < (points[2 * j] - points[2 * i]) * (y - points[2 * i + 1]) /
             (points[2 * j + 1] - points[2 * i + 1]) + points[2 * i])) {
            c = !c;
        }
    }
     for (i = 0; i < numPoints; i += 2) {
        if (x == points[i] && y == points[i + 1]) {
            c = 1;
            break;
        }
    }
    return c;
}

void fillPolygon(int numPoints, int* points) {
    int minX = getmaxx();
    int minY = getmaxy();
    int maxX = 0;
    int maxY = 0;

    // Dolu alanýn sýnýrlarýný hesaplayýn
    for (int i = 0; i < numPoints; i += 2) {
        int x = points[i];
        int y = points[i + 1];
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }

    // Yeþil ile doldurun
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if (pikselKontrol(x, y, numPoints, points)) {
                putpixel(x, y, GREEN);
            }
        }
    }
}

void pikselTarama(int numPoints, int* points) {
    int minX = getmaxx();
    int minY = getmaxy();
    int maxX = 0;
    int maxY = 0;

    // Dolu alanýn sýnýrlarýný hesaplayýn
    for (int i = 0; i < numPoints; i += 2) {
        int x = points[i];
        int y = points[i + 1];
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }

    int squareSize = 10;
    for (int x=0;x<1000;x+= squareSize) {
        for (int y = 0; y < 1000; y += squareSize) {
        	
            if (pikselKontrol(x, y, numPoints, points)) {
                rectangle(x, y, x + squareSize, y + squareSize);
                floodfill((x + x + squareSize) / 2, (y + y + squareSize) / 2, WHITE);
                sayac++;
				}
		}
	}
	printf("\n");
	
}

void KAREBAS(int numPoints, int* points, int squareSize, int squareColor) {
    int minX = getmaxx();
    int minY = getmaxy();
    int maxX = 0;
    int maxY = 0;

    // Dolu alanýn sýnýrlarýný hesaplayýn
    for (int i = 0; i < numPoints; i += 2) {
        int x = points[i];
        int y = points[i + 1];
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }

    // Karelerin rengini ayarla
    setcolor(squareColor);

    for (int x =0; x <= getmaxx(); x++) {
        for (int y =0; y <= getmaxy(); y++) {
            if (pikselKontrol(x, y, numPoints, points)) {
                int isSquareInsidePolygon = 1;
                for (int i = x; i <= x + squareSize; i++) {
                    for (int j = y; j <= y + squareSize; j++) {
                        if (!pikselKontrol(i, j, numPoints, points)) {
                            isSquareInsidePolygon = 0;
                            break;
                        }
                    }
                    if (!isSquareInsidePolygon) {
                        break;
                    }
                }
                if (isSquareInsidePolygon) {
                    rectangle(x, y, x + squareSize, y + squareSize);
                    floodfill((x +x+ squareSize) / 2, (y +y + squareSize) / 2, squareColor);
                }
            }
        }
    }
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, char** output) {
    size_t total_size = size * nmemb;
    // Bellek ayýr ve alýnan veriyi output'a kopyala
    *output = (char*)malloc(total_size + 1);
    if (*output) {
        memcpy(*output, contents, total_size);
        (*output)[total_size] = '\0'; // Null karakter ile sonlandýr
    }
    return total_size;
}
char* satirAl( char* text, int line_number) {
    char* line = strtok(text, "\n"); // Ýlk satýrý al
    int current_line = 1;
    while (line != NULL) {
        if (current_line == line_number) {
            return line; // Ýstenen satýrý bul
        }
        line = strtok(NULL, "\n"); // Bir sonraki satýra geç
        current_line++;
    }
	return NULL; // Ýstenen satýr bulunamadý
}

void drawGrid() {
    int i;
    for(i = 0; i <= getmaxx(); i += 10) {
        setcolor(LIGHTGRAY);
        line(i, 0, i, getmaxy());
    }
    for(i = 0; i <= getmaxy(); i += 10) {
        setcolor(LIGHTGRAY);
        line(0, i, getmaxx(), i);
    }
}

void drawGrid2() {
    int i;
    for(i = 0; i <= getmaxx(); i += 40) {
        setcolor(BLACK	);
        line(i, 0, i, getmaxy());
    }
    for(i = 0; i <= getmaxy(); i += 40) {
        setcolor(BLACK);
        line(0, i, getmaxx(), i);
    }
}

int main()
{
	int gd = DETECT, gm;
    initwindow(1000,1000);
    setbkcolor(WHITE);  // Arka plan rengini siyah yap
	cleardevice();
    drawGrid();
    drawGrid2();
   
    char* specificLine;
     curl_global_init(CURL_GLOBAL_DEFAULT);
    char* url = "http://abilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt";
    char* data = NULL;

    CURL* curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    int satirNum;
    printf("istediginiz satiri giriniz: ");
    scanf("%d",&satirNum);
    if (data) {
        specificLine = satirAl(data, satirNum);
        if (specificLine) {
            printf("Alinan Satir %d: %s\n", satirNum, specificLine);
        } else {
            printf("Satýr %d bulunamadý.\n", satirNum);
        }

        //free(data); // Belleði serbest býrak
    } else {
    	printf("Veri alýnamadý.\n");
    }
    std::string input=specificLine;
    const int MAX_POINTS = 100; // Maksimum koordinat sayýsý
    int points[MAX_POINTS * 2]; // x ve y koordinatlarý için dizi
    int numPoints = 0; // Toplam koordinat sayýsý

    // Koordinatlarý ayýkla ve diziye ekle
    size_t start = input.find("(");
    size_t end;
    while (start != std::string::npos && numPoints < MAX_POINTS * 2) {
        end = input.find(")", start);
        std::string coord = input.substr(start + 1, end - start - 1);
        size_t comma = coord.find(",");
        points[numPoints++] = std::atoi(coord.substr(0, comma).c_str())*10;
        points[numPoints++] = std::atoi(coord.substr(comma + 1).c_str())*10;
        start = input.find("(", end);
    }
    int len= strlen(specificLine);
    int numCount=0;
    int numbers[40];
    for (int i = 1; i < len; i++) {
        if (isdigit(input[i])) {
            char numStr[32]; // Geçici bir karakter dizisi sayýyý saklamak için
            int j = 0;

            // Sayýyý bulmak ve numStr dizisine kopyalamak
            while (i < len && isdigit(input[i])) {
                numStr[j] = input[i];
                i++;
                j++;
            }

            numStr[j] = '\0'; // C-dizesini sonlandýr
            numbers[numCount] = atoi(numStr); // Diziyi tam sayýya çevir
            numCount++;
		}
	}
	
    // Koordinatlarý atayacak deðiþkenler
        int xCoords[20];
        int yCoords[20];
        int numPoint = numCount / 2; // Toplam koordinat sayýsý
        for (int i = 0; i < numCount; i++) {
            if (i % 2 == 0) {
                xCoords[i /2] = numbers[i];
            } else {
            yCoords[i /2] = numbers[i];
        }
    }
    // Alan hesaplama
    int area = 0;
    for (int i = 0; i < numPoint - 1; i++) {
        area += (xCoords[i] * yCoords[i + 1]) - (xCoords[i + 1] * yCoords[i]);
    }
    area += (xCoords[numPoint - 1] * yCoords[0]) - (xCoords[0] * yCoords[numPoint - 1]);
    area = abs(area) / 2;
	printf("Alan: %d\n", area);
    drawpoly(numPoints / 2 , points);
	printf("\n");
	
    char areaMsg[50];
    sprintf(areaMsg, "Alan: %d", area); // 'alan' deðiþkeni çokgenin alanýný içermelidir
    outtextxy((xCoords[0] + xCoords[1] + xCoords[2] + xCoords[3] + xCoords[4]) / 5 , (yCoords[0] + yCoords[1] + yCoords[2] + yCoords[3] + yCoords[4]) / 5 , areaMsg);
	getch();
	closegraph(); // Grafik penceresini kapat
	
	initwindow(1000,1000);  
    drawGrid();
    drawGrid2();
    
    int fillcolor=GREEN;
    drawpoly(numPoints/2,points);
    setfillstyle(SOLID_FILL,fillcolor);
	fillpoly(numPoints / 2 , points);

    // Çokgenin içini doldurur
    setfillstyle(SOLID_FILL, GREEN);
    fillpoly(numPoints/2, points);
    printf("%d",numPoints);
    
	fillPolygon(numPoints/2, points);
	pikselTarama(numPoints/2,points);
    drawGrid();
    drawGrid2();
	int squareSize = 1; // Kare boyutu
    int squareColor = YELLOW; // Kare rengi
    // Eþleþen noktalara kare bastýrma fonksiyonunu çaðýrýn
    KAREBAS(numPoints / 2, points, squareSize, squareColor);
    drawGrid();
    drawGrid2();
    printf("%d",sayac);
    printf("\n");
    int sondaj=0,platform=0,topSondaj=0,topPlat=0,rezerv=sayac*10,topMaliyet=0,kar=0;
    printf("Birim sondaj maliyetini giriniz: "); scanf("%d",&sondaj);
    if(sondaj<=10&&sondaj>=1)
    {
		topSondaj=sayac*sondaj;
	}
	else
	{
		printf("tekrar deger giriniz: ");
	}
    printf("Birim platform maliyetini giriniz: "); scanf("%d",&platform);
    topPlat=platform*sayac;
    printf("toplam sondaj sayisi: %d \n",sayac);
    printf("toplam sondaj maliyeti: %d\n",topSondaj);
    printf("toplam platform sayisi: %d\n",sayac);
    printf("toplam platform maliyeti: %d\n",topPlat);
    topMaliyet=topSondaj+topPlat;
	printf("toplam maliyetiniz: %d\n",topMaliyet);
    kar=rezerv-topMaliyet;
	printf("kar durumunuz: %d$",kar);
    
    getch();
     	  
 }
