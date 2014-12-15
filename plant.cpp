#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std;
#pragma pack(1)
typedef struct tagBitMapFileHeader {
	char           type[2];        		/*  2   0   */
	unsigned int   size;           		/*  4   2   if 12 use BitMapCoreHeader*/
	unsigned short reserved1;     	/*  2   6  not used*/
	unsigned short reserved2;      	/*  2   8  not used*/
	unsigned int   offBits;        		/*  4   10  */
} BitMapFileHeader;                   /* Total size: 14 */
#pragma pack()

#pragma pack(1)
typedef struct tagBitMapInfoHeader {
	unsigned int   size;           		/*  4   0   */
	unsigned int   width;          		/*  4   4   */
	unsigned int   height;         		/*  4   8   */
	unsigned short planes;         	/*  2   12  */
	unsigned short bitCount;       	/*  2   14  */
	unsigned int   compression;    	/*  4   16  */
	unsigned int   sizeImage;      	/*  4   20  */
	unsigned int   XPelsPerMeter;  	/*  4   24  */
	unsigned int   YPelsPerMeter;  	/*  4   28  */
	unsigned int   clrUsed;        		/*  4   32  */
	unsigned int   clrImportant;   	/*  4   36  */
} BitMapInfoHeader;   /* Total size: 40 */
#pragma pack()

#pragma pack(1)
typedef struct tagBitMapCoreHeader {
	unsigned short size;           		/*  4   0   */
	unsigned short width;          		/*  4   4   */
	unsigned short height;         		/*  4   8   */
	unsigned short planes;         	/*  2   12  */
	unsigned short bitCount;       	/*  2   14  */
}BitMapCoreHeader;
#pragma pack()
struct node
{
	unsigned char color[3];
	struct node *next;
};
int padd(int size, int height, int width){
	int bprow, ans;
	bprow = size / height;
	ans = bprow - 3 * width;
	return ans;
}
int main(){
	BitMapFileHeader bmfh1, bmfh2;
	BitMapInfoHeader bmih1, bmih2;
	BitMapCoreHeader bmch1, bmch2;
	FILE *input, *input2, *output, *outdata;
	char filename[256], filename2[256], Ofilename[256], Odatafilename[256];
	int  padding, bprow, padding2, i, count,j;
	double w, b, g,r;
	unsigned char *p, *p2;
	printf("請輸入要處理的圖片1檔名:");
	cin >> filename;
	printf("%s",filename);
	/*printf("請輸入要處理的圖片2檔名:");
	scanf("%s", &filename2);*/
	printf("請輸入輸出檔名:");
	cin >> Ofilename;
	/*printf("請輸入outdata:");
	scanf("%s", &Odatafilename);*/
	input = NULL;
	fopen_s(&input,filename, "rb");

	//input2 = fopen(filename2, "rb");
	fopen_s(&output,Ofilename, "wb");
	//outdata = fopen(Odatafilename, "wb");
	if (input == NULL )
	{
		printf("檔案不存在!!");
		return 0;
	}

	fread(&bmfh1, sizeof(BitMapFileHeader), 1, input);
	//fread(&bmfh2, sizeof(BitMapFileHeader), 1, input2);
	//if(bmfh.size==40)
	fread(&bmih1, sizeof(BitMapInfoHeader), 1, input);
	//fread(&bmih2, sizeof(BitMapInfoHeader), 1, input2);
	/*else
	fread(&bmch, sizeof(BitMapCoreHeader), 1, input);*/
	rewind(input);
	//rewind(input2);
	fseek(input, bmfh1.offBits, SEEK_SET);
	//fseek(input2, bmfh2.offBits, SEEK_SET);
	p = (unsigned char *)malloc(sizeof(unsigned char)*bmih1.sizeImage);
	p2 = (unsigned char *)malloc(sizeof(unsigned char)*bmih1.sizeImage);
	fread(p, bmih1.sizeImage, 1, input);
	//fread(p2, bmih2.sizeImage, 1, input2);
	if (bmfh1.size == 40)
		padding = padd(bmih1.sizeImage, bmih1.height, bmih1.width);
	else
		padding = padd(bmih1.sizeImage, bmih1.height, bmih1.width);//test
	/*if (bmfh2.size == 40)
		padding2 = padd(bmih2.sizeImage, bmih2.height, bmih2.width);
	else
		padding2 = padd(bmih2.sizeImage, bmih2.height, bmih2.width);*///test
	//testing------------------
	printf("FileHeader\n\n");
	printf("offBits:%d\n", bmfh1.offBits);
	printf("reserved1:%d\n", bmfh1.reserved1);
	printf("reserved2:%d\n", bmfh1.reserved2);
	printf("size:%d\n", bmfh1.size);
	printf("type:%d\n", bmfh1.type);
	printf("\nInfoHeader\n\n");
	printf("bitCount:%d\n", bmih1.bitCount);
	printf("clrImportant:%d\n", bmih1.clrImportant);
	printf("clrUsed:%d\n", bmih1.clrUsed);
	printf("compression:%d\n", bmih1.compression);
	printf("height:%d\n", bmih1.height);
	printf("planes:%d\n", bmih1.planes);
	printf("size:%d\n", bmih1.size);
	printf("sizeImage:%d\n", bmih1.sizeImage);
	printf("width:%d\n", bmih1.width);
	printf("XPelsPerMeter:%d\n", bmih1.XPelsPerMeter);
	printf("YPelsPerMeter:%d\n", bmih1.YPelsPerMeter);
/*	for (i = 0, count = 0; i<1000; i += 3, count++){
		if (count == bmih1.width){
			i += padding;
			count = 0;
		}
		fprintf(outdata, "1:\tR: %d\tG: %d\t B %d\t 2:\tR: %d\tG: %d\tB: %d\n", *(p + i), *(p + i + 1), *(p + i + 2), *(p2 + i), *(p2 + i + 1), *(p2 + i + 2));

	}*/
	//process------------------
	cout << "paddying : " << padding << endl;
	for (i = 0,j=0,w=0,b=0,g=0,r=0; i<bmih1.sizeImage; i+=3,j++){
		if (j %(bmih1.width)==0 &&j!=0)
			i += padding;
	/*	*(p2 + i) = *(p + i);
		*(p2 + i + 1) = *(p + i + 1);
		*(p2 + i + 2) = *(p + i + 2);*/
		//printf("%d\t%d\t%d\n",*(p+i),*(p+i+1),*(p+i+2));
		if (*(p + i)+*(p+i+1)+*(p+i+2)>740)
			w++;
		else if (*(p + i) + *(p + i + 1) + *(p + i + 2) < 50)
			b++;
		else if (*(p + i + 2) >= 170)
			r++;
		else{
			g++;
			*(p + i) = 0;
			*(p+ i + 1) = 255;
			*(p+ i + 2) = 255;
		}
		
	}
	cout << "w : " << w << " b : " << b << " g : " << g <<" r : "<<r<<" "<< (double)(g / (b + g))<<endl;
	system("PAUSE");
	// write file--------------
	fwrite(&bmfh1, sizeof(BitMapFileHeader), 1, output);
	fwrite(&bmih1, sizeof(BitMapInfoHeader), 1, output);
	rewind(output);
	fseek(output, bmfh1.offBits, SEEK_SET);
	fwrite(p, bmih1.sizeImage, 1, output);
	free(p);
//	free(p2);
	fclose(input);
	//fclose(input2);
	fclose(output);
	return 0;
}
