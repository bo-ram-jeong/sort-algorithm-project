#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

int match(char *userName, char *animalName) {
	//알파벳당 획수
	int stroke[26] = { 3, 2, 1, 2, 4, 3, 1, 3, 1, 1, 3, 1, 3, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 1 };
	int u = strlen(userName);
	int a = strlen(animalName);
	int shorterLen = u > a ? a : u;	//더 짧은 이름길이 

	//교차해서 넣을 문자열 배열 생성
	char nameArr[40];	
	int index = 0;
	for (int i = 0; i < shorterLen; i++) {
		nameArr[index] = userName[i];
		nameArr[++index] = animalName[i];
		index++;
	}
	//더 긴 이름 포인터배열에 넣기
	char *longerName;	
	longerName = u > a ? userName : animalName;
	//남은 이름 이어서 붙이기
	for (int j = 0; j < strlen(longerName)- shorterLen; j++) {
		nameArr[ j + shorterLen *2 ] = longerName[ j + shorterLen];
	}

	//최초 점수 배열 생성
	char scoreArr[40];
	int i ;
	for (i = 0; i < (u + a); i++) {
		int alphabetIndex = (int)nameArr[i]- (int)'A';
		scoreArr[i] = stroke[alphabetIndex];
	}
	//점수 계산
	for (i = 0; i < (u + a) - 2; i++) {
		for (int j = 0; j < (u + a) - i - 1; j++) {
			scoreArr[j] += scoreArr[j + 1];
			scoreArr[j] %= 10;
		}
	}
	// 특정 자리수 추출 방법: 일의 자리는 % 10, 십의 자리는 나누기 10 해서 몫만 취한 후 % 10
	return (scoreArr[0] % 10 * 10 + scoreArr[1] % 10);
}
void intswap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
void sort(char p[][20], char a[][20], int* c, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (c[i] > c[j])
			{
				intswap(&p[i], &p[j]);
				intswap(&a[i], &a[j]);
				intswap(&c[i], &c[j]);
			}
		}
	}
}


int main() {
	int so;
	int num = 1;

	char animals[][20] = { "DOG(개)", "CAT(토끼)", "PANDA(판다)", "RABBIT(토끼)", "SHEEP(양)", "MOUSE(쥐)", "LION(사자)", "TIGER(호랑이)", "PIG(돼지)", "BEAR(곰)" };

	char userName[20];	//사용자이름배열
	char animalName[20];	//동물이름배열
	int matchPercent = 0;	//궁합퍼센트
	char answer1 = 'N';
	char answer='N';

	char uN[100][20];
	char aN[100][20];

	int matchArr[10] = {};
	int matchIndex = 0;
	//궁합배열에 -1로 초기화
	for (int i = 0; i < 10; i++) {
		matchArr[i] = -1;
	}	

	char min[10];
	char temp[10];
	char choose1='Z';
	int choose2;

	printf("<< 동물이름으로 알아보는 알고리즘 >>\n\n");
	//동물이름 출력
	int row = sizeof(animals) / sizeof(animals[0]);
	for (int i = 0; i < row; i++) {
		printf(animals[i]);
		printf("  ");
	}
	do {
		printf("\n\n위의 나열된 동물로 어떤 것을 보시겠습니까?\n");
		printf("A : 동물 사전 보기\n");
		printf("B : 동물 궁합 보기\n==> ");
		scanf_s("\n%c", &choose1, 1);

		if ((choose1 == 'A') || (choose1 == 'a')) {
			printf("\n1. A ~ Z  /  2. Z ~ A");
			printf("\n위의 원하는 정렬 방식을 선택해주세요.(1 or 2) : ");
			scanf("%d", &choose2);

			//대문자로 바꿔주는 거 넣어주기
			if (choose2 == 1) { // 첫번째 선택정렬 적용했을 때
				for (int i = 0; i < 10; i++) {
					for (int j = i + 1; j < 10; j++) {
						if (strcmp(animals[i], animals[j]) > 0) {
							strcpy(min, animals[i]);
							strcpy(animals[i], animals[j]);
							strcpy(animals[j], min);
						}
					}
				}

				printf("\n동물 이름을 A~Z순서대로 출력합니다.\n");
				for (int i = 0; i < 10; i++) {
					printf("%s\n", animals[i]);
				}
			}
			else if (choose2 == 2) {  //두번째 버블정렬 적용했을 때
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 9 - i; j++) {
						if (strcmp(animals[j], animals[j + 1]) < 0) {
							strcpy(temp, animals[j + 1]);
							strcpy(animals[j + 1], animals[j]);
							strcpy(animals[j], temp);
						}
					}
				}
				printf("\n동물 이름을 Z~A 순서대로 출력합니다.\n");
				for (int i = 0; i < 10; i++) {
					printf("%s\n", animals[i]);
				}
			}
		}
		else if ((choose1 == 'B') || (choose1 == 'b')) {
			printf("\n[ 나와 어울리는 동물 궁합 TEST ]\n\n");
			//동물이름 출력
			int row = sizeof(animals) / sizeof(animals[0]);
			for (int i = 0; i < row; i++) {
				printf(animals[i]);
				printf("  ");
			}
			do {
				printf("\n\n사용자의 이름을 영어로 입력해주세요(ex.MINJU) : ");
				scanf_s("%s", userName, sizeof(userName));
				//대문자로 변환
				for (int i = 0; i < 20; i++) {
					if ((userName[i] >= 'a') && (userName[i] <= 'z'))
					{
						userName[i] = userName[i] - 'a' + 'A';
					}
				}
				printf("위의 나열된 동물들 중 하나의 동물을 영어로 입력해주세요(ex.CAT) : ");
				scanf_s("%s", animalName, sizeof(animalName));
				//대문자로 변환
				for (int i = 0; i < 20; i++) {
					if ((animalName[i] >= 'a') && (animalName[i] <= 'z'))
					{
						animalName[i] = animalName[i] - 'a' + 'A';
					}
				}

				//궁합퍼센트구하기
				matchPercent = match(userName, animalName);

				printf("\n%s와(과) %s의 궁합은 %d%% 입니다!\n\n", userName, animalName, matchPercent);
				//지금까지 한 궁합퍼센트를 궁합배열에 넣기
				matchArr[matchIndex] = matchPercent;
				strcpy(uN[matchIndex], userName);
				strcpy(aN[matchIndex], animalName);
				matchIndex++;

				printf("동물과의 궁합을 더 보시겠습니까? Y/N => ");
				scanf_s("\n%c", &answer, 1);

			} while ((answer == 'Y') || (answer == 'y'));


			//test 궁합 들어간 배열
			printf("\n[ 현재까지의 궁합 나열 ]\n");
			for (int i = 0; i < 10; i++) {
				printf("%d\t", matchArr[i]);
			}

			//대답이 Y가 아닐때 
			if (!(answer == 'Y') || (answer == 'y')) {
				//궁합배열에 원소가 하나일때
				if (matchArr[1] == -1) {
					printf("\n!! 궁합정렬을 확인하려면 동물과의 궁합을 2번 이상 입력해주셔야 합니다.\n\n");
				}
				else {
					printf("\n1. 궁합 낮은 순  /  2. 궁합 높은 순");
					printf("\n위의 원하는 정렬 방식을 선택해주세요.(1 or 2) : ");
				}
				while (scanf("%d", &so) == 0 || (so != 1 && so != 2)){
					printf("1 또는 2로만 입력해야 합니다. 다시 입력해주세요 :");
					getchar();
				}

				if (so == 1) // 1일 경우 (궁합 낮은 순)
				{
					sort(uN, aN, matchArr, matchIndex);

					printf("\n결과 (궁합 낮은 순) :\n");
					for (int i = 0; i < matchIndex; i++)
						printf("%d. 사용자 이름 : %s\t동물 이름 : %s\t   궁합율 : %d\n", num++, uN[i], aN[i], matchArr[i]);
				}
				else // 2일 경우 (궁합 높은 순)
				{
					sort(uN, aN, matchArr, matchIndex);

					printf("\n결과 (궁합 높은 순) :\n");
					for (int i = matchIndex - 1; i >= 0; i--)
						printf("%d. 사용자 이름 : %s\t동물 이름 : %s\t   궁합율 : %d\n", num++, uN[i], aN[i], matchArr[i]);
				}
				
			}
		}
		else
			printf("\nA 또는 B로 입력해주세요!");
		printf("\n다른 보기를 다시 선택하시겠습니까? Y/N => ");
		scanf_s("\n%c", &answer1, 1);
	}while ((answer1 == 'Y') || (answer1 == 'y'));

	//대답이 Y가 아닐때 
	if (!(answer1 == 'Y') || (answer1 == 'y')) {
		printf("\n프로그램을 종료합니다.\n\n");
	}
	system("pause");
	return 0;
}