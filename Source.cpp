#define _CRT_SECURE_NO_WARNINGS // ��� ���������� ������ scanf()
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <math.h>

int** arr;
int* save;
FILE* fp;
int* path;
int* pow1;


void print_result(int* path1, int count)
{
	printf("��������� ������: \n������ ����������� ���� \n");
	for (int i = 0; i < count; i++)
		printf(" %d ", path1[i] + 1);

	// ���������� ��� ��� ������ �������, ����� �������� ������ ����
	printf(" %d ", path1[0] + 1);
	printf("\n");
}


bool check_vertex(int v, int** graph, int path[], int pos)
{
	
	if (graph[path[pos - 1]][v] == 0)
		return false;
	
	for (int i = 0; i < pos; i++)
		if (path[i] == v)
			return false;

	return true;
}

bool ham_Cycle(int** graph, int path[], int pos, int count)
{
	
	if (pos == count)
	{
		
		if (graph[path[pos - 1]][path[0]] == 1)
			return true;
		else
			return false;
	}

	
	for (int v = 1; v < count; v++)
	{
		
		if (check_vertex(v, graph, path, pos))
		{
			path[pos] = v;
			if (ham_Cycle(graph, path, pos + 1, count) == true)
				return true;
			path[pos] = -1;
		}
	}

	
	return false;
}



int** dynamic(int count) {

	int** mass;
	mass = (int**)malloc(count * sizeof(int*));
	for (int i = 0; i < count; i++) mass[i] = (int*)malloc(count * sizeof(int));
	return mass;

}

int* dynamic_path(int count) {
	int* path1;
	path1 = (int*)malloc(count * sizeof(int));
	return path1;
}

int* dynamic_pow(int count) {

	int* pow_vertex;
	pow_vertex = (int*)malloc(count * sizeof(int));
	return pow_vertex;

}

void generate_path(int* path1, int count) {
	for (int i = 0; i < count; i++) {
		path1[i] = -1;
	}
}

void generate_pow1(int* massiv, int count) {
	for (int i = 0; i < count; i++) {
		massiv[i] = 0;
	}
}

void generate_matrix(int** mass, int count, int ver) {  //������������ �����������������
	int chance;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			chance = rand() % 101;
			if (chance < ver){
				mass[i][j] = 1;
				mass[j][i] = mass[i][j];
			}
			else {
				mass[i][j] = 0;
				mass[j][i] = mass[i][j];
			}
			if (i == j) mass[i][j] = 0;
		}
	}
}


void print(int** mass, int count) {
	printf("|�|  ");
	for (int k = 1; k <= count; k++) printf("|%d| ", k);
	printf("\n");
	for (int i = 0; i < count; i++) {
		printf("\n|%d| ", i + 1);
		for (int j = 0; j < count; j++) {
			printf("%3d ", mass[i][j]);
		}
		printf("\n");
	}
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	int size = 0;
	
	char name[50];
	char name_save[50];
	char OPEN = 'A'; // �������, ��� ������� ������� ������� �������� ����
	int MENU;
	int n=0;
	int s, k = 0;
	int v;
	int num;
	bool test = false;
	bool test1 = false;
	int pow_vertex;
	int chance = 0;
	int chet = 0;

	do {
		printf("\n����:\n");
		printf("1 - ��������� ���� �� �����\n2 - ������������� ���� � ���������\n3 - ��������� ���������� � ����\n4 - �����\n");
		printf("�������� ����� �� ����: ");
		scanf_s("%d", &MENU);
		
		printf("\n");
		if ((MENU != 1) && (MENU != 2) && (MENU != 3) && (MENU != 4)) {	// �������� ������������ ����� ������
			system("cls");			
			printf("\n������������ ����, ���������� �����!\n");
		}

		if (MENU == 1) {
			test = true;
			printf("������� �������� ����� �� �������� ����� ����������� ������ ��������, �� ����� 50 �������� (������: mass.txt):");

			//gets_s(name);
			scanf_s("%s", &name, 50);

			if ((fp = fopen(name, "r")) == NULL) {
				while ((OPEN != '1') && (OPEN != '2')) {
					printf("������ ���� �� ������. ��������� � ������������ ����� �������� �����!\n");
					printf("��� ������ �� ��������� ������� - 1\n");
					scanf_s("%c", &OPEN, 1);
					if (OPEN == '1') {
						system("cls");
						exit(1);
					}
				}
			}
			
		
			if (OPEN == 'A') {
				while ((fscanf(fp, "%d", &s) != EOF)) {
					v = (fscanf(fp, "%d", &s));
					if (v == 0) {
						printf("�������� ������ ������! ��������� ����.\n");
						exit(0);
						break;
					}
				}
			}
			fclose(fp);
			fp = fopen(name, "r");
			// ���������� ������ � �����
			if (OPEN == 'A') {	// ���� ���������� ����� '�' => ������� ������� ����
				while ((fscanf(fp, "%d", &s) != EOF)) {
					if (!fp) break;
					n += 1;
				}
				rewind(fp); // ������������ ���� ��� ���������� ������
				num = sqrt(n);
				printf("%d\n", num);
				arr = dynamic(num);
				for (int i = 0; i < num; i++) {
					for (int j = 0; j < num; j++) {
						fscanf_s(fp, "%d", &arr[i][j]);
					}
				}
				printf("������ ������ �� �����.\n");
				print(arr, num);
				fclose(fp);
			}


				pow1 = dynamic_pow(num);
				generate_pow1(pow1, num);
				for (int i = 0; i < num; i++) {
					pow_vertex = 0;
					for (int j = 0; j < num; j++) {
						if (arr[i][j] > 0) pow_vertex++;
					}
					pow1[i] = pow_vertex;
				}

				for (int i = 0; i < num; i++) {
					if (pow1[i] > 2) chet++;					
				}

				if (chet == num) {
			
					printf("\n� ������ ����� �������� ���������� ����������� ����\n");
					printf("\n���������� ����� �����\n");

					path = dynamic_path(num);
					generate_path(path, num);
					
					path[0] = 0;
					if (ham_Cycle(arr, path, 1, num) == false)
					{
						printf("\n����������� ���� �� ������!");
						test1 = true;
						return false;
					}
					print_result(path, num);
				}
				else {
					system("cls");
					printf("\n� ������ ����� ����������� ���� �� ����������, ��� ��� ��� ������� ������ ����� ������� ������ 2!");
					test1 = true;
				}

				chet = 0;
							
		}

		
		if (MENU == 2) {

			printf("������� ������� �������: ");
			scanf_s("%d", &size);
			printf("������� ����������� ��������� ����� ����� ���������: ");
			scanf_s("%d", &chance);
			arr = dynamic(size);
			generate_matrix(arr, size, chance);
			print(arr, size);

			pow1 = dynamic_pow(size);
			generate_pow1(pow1, size);
			for (int i = 0; i < size; i++) {
				pow_vertex = 0;
				for (int j = 0; j < size; j++) {
					if (arr[i][j] > 0) pow_vertex++;
				}
				pow1[i] = pow_vertex;
			}

			for (int i = 0; i < size; i++) {
				if (pow1[i] > 2) chet++;
			}

			if (chet == size) {

				printf("\n� ������ ����� �������� ���������� ����������� ����");
				printf("\n���������� ����� �����\n");

				

				path = dynamic_path(size);
				generate_path(path, size);
				path[0] = 0;
				if (ham_Cycle(arr, path, 1, size) == false)
				{
					printf("\n����������� ���� �� ������!");
					test1 = true;
					return false;
				}
				print_result(path, size);
			}
			else {
			
				printf("\n� ������ ����� ����������� ���� �� ����������, ��� ��� ��� ������� ������ ����� ������� ������ 2!");
				test1 = true;
			}		
			chet = 0;
		}

		if (MENU == 3) {
			if (test == true) {
				size = num;
			}
			printf("������� �������� �����, � ������� ������ �� ��������� �������, � ��������� ���� ����� ����� ����� (�� ����� 50 ��������): ");
			scanf_s("%s", name_save, 50);
			if ((fp = fopen(name_save, "w")) == NULL) {
				system("cls");
				printf("\n�� ������� ������� ����!\n");
				return 0;
			}

			fprintf(fp, "��������� ������ ���������:\n");
			
			for (int k = 1; k <= size; k++) fprintf(fp,"%d ", k);
			fprintf(fp,"\n -----------\n");
			for (int i = 0; i < size; i++) {
				fprintf(fp,"%d |", i + 1);
				for (int j = 0; j < size; j++) {
					fprintf(fp,"%d ", arr[i][j]);
				}
				fprintf(fp,"\n");
			}

			if (test1 == false) {

				fprintf(fp, "��������� ������:"
					" ������ ����������� ���� \n");
				for (int i = 0; i < size; i++)
					fprintf(fp, " %d ", path[i] + 1);

				// ���������� ��� ��� ������ �������, ����� �������� ������ ����
				fprintf(fp, " %d ", path[0] + 1);
				fprintf(fp, "\n");
			}
			else {
				fprintf(fp, "\n����������� ���� �� ������!");
			}
			fclose(fp);
			printf("\n���������� ������� ��������� � ����� - %s\n", name_save);
		}

	} while (MENU != 4);

	system("pause");

}