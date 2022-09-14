#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_YEAR_DURATION	10	// 기간

// 구조체 선언
typedef struct {
	char	name[20];		// 이름
	char	sex;			// 성별 M or F
	int		freq[MAX_YEAR_DURATION]; // 연도별 빈도
} tName;

typedef struct {
	int		len;		// 배열에 저장된 이름의 수
	int		capacity;	// 배열의 용량 (배열에 저장 가능한 이름의 수)
	tName	*data;		// 이름 배열의 포인터
} tNames;

// 함수 원형 선언

// 연도별 입력 파일을 읽어 이름 정보(이름, 성별, 빈도)를 이름 구조체에 저장
// 이미 구조체에 존재하는(저장된) 이름은 해당 연도의 빈도만 저장
// 새로 등장한 이름은 구조체에 추가
// 주의사항: 동일 이름이 남/여 각각 사용될 수 있으므로, 이름과 성별을 구별해야 함
// 주의사항: 구조체 배열은 정렬 리스트(ordered list)이어야 함
// 이미 등장한 이름인지 검사하기 위해 bsearch 함수를 사용
// 새로운 이름을 저장할 메모리 공간을 확보하기 위해 memmove 함수를 이용하여 메모리에 저장된 내용을 복사
// names->capacity는 2배씩 증가
void load_names( FILE *fp, int year_index, tNames *names);

// 구조체 배열을 화면에 출력
void print_names( tNames *names, int num_year);

// bsearch를 위한 비교 함수
int compare( const void *n1, const void *n2);

// 이진탐색 함수
// return value: key가 발견되는 경우, 배열의 인덱스
//				key가 발견되지 않는 경우, key가 삽입되어야 할 배열의 인덱스
int binary_search( const void *key, const void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));

// 함수 정의

// 이름 구조체 초기화
// len를 0으로, capacity를 1로 초기화
// return : 구조체 포인터
tNames* create_names(void)
{
	tNames* pnames = (tNames*)malloc(sizeof(tNames));

	pnames->len = 0;
	pnames->capacity = 1;
	pnames->data = (tName*)malloc(pnames->capacity * sizeof(tName));

	return pnames;
}
// 이름 구조체에 할당된 메모리를 해제
void destroy_names(tNames *pnames)
{
	free(pnames->data);
	pnames->len = 0;
	pnames->capacity = 0;

	free(pnames);
}
	
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	tNames *names;
	
	int num = 0;
	FILE *fp;
	int num_year = 0;
	
	if (argc == 1) return 0;

	// 이름 구조체 초기화
	names = create_names();

	// 첫 연도 알아내기 "yob2009.txt" -> 2009
	int start_year = atoi( &argv[1][3]);
	
	for (int i = 1; i < argc; i++)
	{
		num_year++;
		fp = fopen( argv[i], "r");
		assert( fp != NULL);
		
		int year = atoi( &argv[i][3]); // ex) "yob2009.txt" -> 2009
		
		fprintf( stderr, "Processing [%s]..\n", argv[i]);
		
		// 연도별 입력 파일(이름 정보)을 구조체에 저장
		load_names(fp, year-start_year, names);
		
		fclose( fp);
	}
	
	// 이름 구조체를 화면에 출력
	print_names(names, num_year);

	// 이름 구조체 해제
	destroy_names( names);
	
	return 1;
}

void load_names(FILE* fp, int year_index, tNames* names) {

	char temp[30];
	char check = 0;
	int n;

	while (fgets(temp, sizeof(temp), fp) != NULL) 
	{
		char name_temp[20] = { 0, }; // 임시로 이름을 담을 문자열 배열
		char freq_temp[10] = { 0, }; // 임시로 빈도수를 담을 문자열 배열
		char sex_temp; // 임시로 성별을 담을 char
		for (int i = 0; i < strlen(temp); i++) { // 쉼표가 있는 문자열 인덱스를 얻는 코드
			if (temp[i] == ',') { // 쉼표를 발견했다면
				for (int j = 0; j < i; j++) name_temp[j] = temp[j]; // 쉼표 전까지의 문자열을 모두 복사
				sex_temp = temp[i + 1]; // 성별 복사
				int k = 0;
				for (int j = i + 3; j < strlen(temp) - 1; j++) {
					freq_temp[k++] = temp[j]; // 빈도수 복사
				}
				break; // for문 탈출(break는 for, while 탈출)
			}
		} 

		tName *newName = (tName *)malloc(sizeof(tName));
		memset(&newName, 0, sizeof(tName));
		strcpy(newName->name, name_temp);
		newName->sex = sex_temp;
		
		n = binary_search(newName, names->data, names->len, sizeof(tName), compare);
		
		memset(&newName, 0, sizeof(tName));
		free(newName);

		if (!strcmp(name_temp, names->data[n].name) && sex_temp == names->data[n].sex) {
				names->data[n].freq[year_index] = atoi(freq_temp);
				check = 1;
				break; //
			}
		
		if (check) { // check가 1이면 위의 경우에 포함되므로 다음 줄을 입력받기 위해 continue로 넘어간다.
			check = 0;
			continue;
		}

		memmove(&(names->data[n+1]),&(names->data[n]),sizeof(tName));

		memset(&(names->data[n]), 0, sizeof(tName));
		
		strcpy(names->data[n].name, name_temp);
		names->data[n].freq[year_index] = atoi(freq_temp);
		names->data[n].sex = sex_temp;
		(names->len)++;
		//구조체를 추가로 할당하는 코드
		if ((names->len) == (names->capacity)) {
			(names->capacity) *= 2;
			names->data = realloc(names->data, sizeof(tName) * (names->capacity));

		}

	}
}

void print_names(tNames* names, int num_year) {
	for (int i = 0; i < names->len; i++) {
		printf("%s\t%c\t", (names->data[i]).name, (names->data[i]).sex);
		for (int j = 0; j < num_year; j++) {
			printf("%d\t", (names->data[i]).freq[j]);
		}
		printf("\n");
	}
}

int compare(const void* n1, const void* n2) {
	tName* a = (tName*) n1;
	tName* b = (tName*) n2;

	if (strcmp(a->name, b->name) == 0) {
		if (a->sex > b->sex)
			return 1;
		else
			return -1;
	}
	else return(strcmp(a->name, b->name));
}

int binary_search(const void* key, const void* base, size_t nmemb, size_t size, int (*compare)(const void*, const void*)) {

	tName *x = (tName*)key;
	tName *left = (tName*)base;

	int index_left = 0;
	int index_right = nmemb - 1;
	int index_mid = (index_left + index_right) / 2;
	tName* mid = left + index_mid;

	while( index_left <= index_right )
	{

		if (compare( x, mid ) == 1) { //x가 더 클 때
			index_left = index_mid + 1;	
		}
		else { //x
			index_right = index_mid - 1;
		}

		index_mid = (index_left + index_right) / 2;
		mid = left + index_mid;
	}

	return index_left;

}
