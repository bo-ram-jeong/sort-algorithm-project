#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

int match(char *userName, char *animalName) {
	//���ĺ��� ȹ��
	int stroke[26] = { 3, 2, 1, 2, 4, 3, 1, 3, 1, 1, 3, 1, 3, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 1 };
	int u = strlen(userName);
	int a = strlen(animalName);
	int shorterLen = u > a ? a : u;	//�� ª�� �̸����� 

	//�����ؼ� ���� ���ڿ� �迭 ����
	char nameArr[40];	
	int index = 0;
	for (int i = 0; i < shorterLen; i++) {
		nameArr[index] = userName[i];
		nameArr[++index] = animalName[i];
		index++;
	}
	//�� �� �̸� �����͹迭�� �ֱ�
	char *longerName;	
	longerName = u > a ? userName : animalName;
	//���� �̸� �̾ ���̱�
	for (int j = 0; j < strlen(longerName)- shorterLen; j++) {
		nameArr[ j + shorterLen *2 ] = longerName[ j + shorterLen];
	}

	//���� ���� �迭 ����
	char scoreArr[40];
	int i ;
	for (i = 0; i < (u + a); i++) {
		int alphabetIndex = (int)nameArr[i]- (int)'A';
		scoreArr[i] = stroke[alphabetIndex];
	}
	//���� ���
	for (i = 0; i < (u + a) - 2; i++) {
		for (int j = 0; j < (u + a) - i - 1; j++) {
			scoreArr[j] += scoreArr[j + 1];
			scoreArr[j] %= 10;
		}
	}
	// Ư�� �ڸ��� ���� ���: ���� �ڸ��� % 10, ���� �ڸ��� ������ 10 �ؼ� �� ���� �� % 10
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

	char animals[][20] = { "DOG(��)", "CAT(�䳢)", "PANDA(�Ǵ�)", "RABBIT(�䳢)", "SHEEP(��)", "MOUSE(��)", "LION(����)", "TIGER(ȣ����)", "PIG(����)", "BEAR(��)" };

	char userName[20];	//������̸��迭
	char animalName[20];	//�����̸��迭
	int matchPercent = 0;	//�����ۼ�Ʈ
	char answer1 = 'N';
	char answer='N';

	char uN[100][20];
	char aN[100][20];

	int matchArr[10] = {};
	int matchIndex = 0;
	//���չ迭�� -1�� �ʱ�ȭ
	for (int i = 0; i < 10; i++) {
		matchArr[i] = -1;
	}	

	char min[10];
	char temp[10];
	char choose1='Z';
	int choose2;

	printf("<< �����̸����� �˾ƺ��� �˰��� >>\n\n");
	//�����̸� ���
	int row = sizeof(animals) / sizeof(animals[0]);
	for (int i = 0; i < row; i++) {
		printf(animals[i]);
		printf("  ");
	}
	do {
		printf("\n\n���� ������ ������ � ���� ���ðڽ��ϱ�?\n");
		printf("A : ���� ���� ����\n");
		printf("B : ���� ���� ����\n==> ");
		scanf_s("\n%c", &choose1, 1);

		if ((choose1 == 'A') || (choose1 == 'a')) {
			printf("\n1. A ~ Z  /  2. Z ~ A");
			printf("\n���� ���ϴ� ���� ����� �������ּ���.(1 or 2) : ");
			scanf("%d", &choose2);

			//�빮�ڷ� �ٲ��ִ� �� �־��ֱ�
			if (choose2 == 1) { // ù��° �������� �������� ��
				for (int i = 0; i < 10; i++) {
					for (int j = i + 1; j < 10; j++) {
						if (strcmp(animals[i], animals[j]) > 0) {
							strcpy(min, animals[i]);
							strcpy(animals[i], animals[j]);
							strcpy(animals[j], min);
						}
					}
				}

				printf("\n���� �̸��� A~Z������� ����մϴ�.\n");
				for (int i = 0; i < 10; i++) {
					printf("%s\n", animals[i]);
				}
			}
			else if (choose2 == 2) {  //�ι�° �������� �������� ��
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 9 - i; j++) {
						if (strcmp(animals[j], animals[j + 1]) < 0) {
							strcpy(temp, animals[j + 1]);
							strcpy(animals[j + 1], animals[j]);
							strcpy(animals[j], temp);
						}
					}
				}
				printf("\n���� �̸��� Z~A ������� ����մϴ�.\n");
				for (int i = 0; i < 10; i++) {
					printf("%s\n", animals[i]);
				}
			}
		}
		else if ((choose1 == 'B') || (choose1 == 'b')) {
			printf("\n[ ���� ��︮�� ���� ���� TEST ]\n\n");
			//�����̸� ���
			int row = sizeof(animals) / sizeof(animals[0]);
			for (int i = 0; i < row; i++) {
				printf(animals[i]);
				printf("  ");
			}
			do {
				printf("\n\n������� �̸��� ����� �Է����ּ���(ex.MINJU) : ");
				scanf_s("%s", userName, sizeof(userName));
				//�빮�ڷ� ��ȯ
				for (int i = 0; i < 20; i++) {
					if ((userName[i] >= 'a') && (userName[i] <= 'z'))
					{
						userName[i] = userName[i] - 'a' + 'A';
					}
				}
				printf("���� ������ ������ �� �ϳ��� ������ ����� �Է����ּ���(ex.CAT) : ");
				scanf_s("%s", animalName, sizeof(animalName));
				//�빮�ڷ� ��ȯ
				for (int i = 0; i < 20; i++) {
					if ((animalName[i] >= 'a') && (animalName[i] <= 'z'))
					{
						animalName[i] = animalName[i] - 'a' + 'A';
					}
				}

				//�����ۼ�Ʈ���ϱ�
				matchPercent = match(userName, animalName);

				printf("\n%s��(��) %s�� ������ %d%% �Դϴ�!\n\n", userName, animalName, matchPercent);
				//���ݱ��� �� �����ۼ�Ʈ�� ���չ迭�� �ֱ�
				matchArr[matchIndex] = matchPercent;
				strcpy(uN[matchIndex], userName);
				strcpy(aN[matchIndex], animalName);
				matchIndex++;

				printf("�������� ������ �� ���ðڽ��ϱ�? Y/N => ");
				scanf_s("\n%c", &answer, 1);

			} while ((answer == 'Y') || (answer == 'y'));


			//test ���� �� �迭
			printf("\n[ ��������� ���� ���� ]\n");
			for (int i = 0; i < 10; i++) {
				printf("%d\t", matchArr[i]);
			}

			//����� Y�� �ƴҶ� 
			if (!(answer == 'Y') || (answer == 'y')) {
				//���չ迭�� ���Ұ� �ϳ��϶�
				if (matchArr[1] == -1) {
					printf("\n!! ���������� Ȯ���Ϸ��� �������� ������ 2�� �̻� �Է����ּž� �մϴ�.\n\n");
				}
				else {
					printf("\n1. ���� ���� ��  /  2. ���� ���� ��");
					printf("\n���� ���ϴ� ���� ����� �������ּ���.(1 or 2) : ");
				}
				while (scanf("%d", &so) == 0 || (so != 1 && so != 2)){
					printf("1 �Ǵ� 2�θ� �Է��ؾ� �մϴ�. �ٽ� �Է����ּ��� :");
					getchar();
				}

				if (so == 1) // 1�� ��� (���� ���� ��)
				{
					sort(uN, aN, matchArr, matchIndex);

					printf("\n��� (���� ���� ��) :\n");
					for (int i = 0; i < matchIndex; i++)
						printf("%d. ����� �̸� : %s\t���� �̸� : %s\t   ������ : %d\n", num++, uN[i], aN[i], matchArr[i]);
				}
				else // 2�� ��� (���� ���� ��)
				{
					sort(uN, aN, matchArr, matchIndex);

					printf("\n��� (���� ���� ��) :\n");
					for (int i = matchIndex - 1; i >= 0; i--)
						printf("%d. ����� �̸� : %s\t���� �̸� : %s\t   ������ : %d\n", num++, uN[i], aN[i], matchArr[i]);
				}
				
			}
		}
		else
			printf("\nA �Ǵ� B�� �Է����ּ���!");
		printf("\n�ٸ� ���⸦ �ٽ� �����Ͻðڽ��ϱ�? Y/N => ");
		scanf_s("\n%c", &answer1, 1);
	}while ((answer1 == 'Y') || (answer1 == 'y'));

	//����� Y�� �ƴҶ� 
	if (!(answer1 == 'Y') || (answer1 == 'y')) {
		printf("\n���α׷��� �����մϴ�.\n\n");
	}
	system("pause");
	return 0;
}