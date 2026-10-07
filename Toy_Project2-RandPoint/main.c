#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>

struct MemoryStruct {

	char* memory;
	size_t size;
};

static size_t WriteMemoryCallBack(void *contents, size_t size, size_t nmemb, void *userp) {

	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)userp;

	char* ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr) {

		printf("메모리 부족(realloc 실패)\n");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

int main(void) {

	srand(time(NULL));

	double latitude; // 위도
	double longitude; // 경도

	int select;

	printf("입력할 값 선택(1. 위도/2. 경도/3. 둘 다 입력/4. 완전 랜덤)\n");
	scanf_s("%d", &select);

	if (select == 1) {

		printf("=======================================\n");
		printf("주의: -90~90사이의 값을 입력해 주세요.\n");
		printf("=======================================\n");

		printf("위도를 입력해 주세요(실수형): ");
		scanf_s("%lf", &latitude);

		double lon_min = -180.0;
		double lon_max = 180.0;
		longitude = lon_min + (double)rand() / RAND_MAX * (lon_max - lon_min);

		printf("위도: %f / 경도: %f\n", latitude, longitude);
		printf("=======================================\n");
		printf(" 생성된 좌표의 구글 맵 링크: ");
		printf(" https://www.google.com/maps/search/?api=1&query=%f,%f\n", latitude, longitude);
		printf("생성된 좌표의 구글 어스 링크: ");
		printf("https://earth.google.com/web/@%f,%f,19000a\n", latitude, longitude);
		printf("=======================================\n");
	} else if (select == 2) {

		printf("=======================================\n");
		printf("주의: -180~180사이의 값을 입력해 주세요.\n");
		printf("=======================================\n");

		printf("경도를 입력해주세요(실수형): ");
		scanf_s("%lf", &longitude);

		double lat_min = -90.0;
		double lat_max = 90.0;		latitude = lat_min + (double)rand() / RAND_MAX * (lat_max - lat_min);

		printf("위도: %f / 경도: %f\n", latitude, longitude);
		printf("=======================================\n");
		printf(" 생성된 좌표의 구글 맵 링크: ");
		printf(" https://www.google.com/maps/search/?api=1&query=%f,%f\n", latitude, longitude);
		printf("생성된 좌표의 구글 어스 링크: ");
		printf("https://earth.google.com/web/@%f,%f,19000a\n", latitude, longitude);
		printf("=======================================\n");
	} else if (select == 3) {
	
		printf("=================================================\n");
		printf("주의: 위도는 -90~90사이의 값을 입력해 주세요.\n");
		printf("주의: 경도는 -180~180사이의 값을 입력해 주세요.\n");
		printf("=================================================\n");

		printf("위도를 입력해 주세요(실수형): ");
		scanf_s("%lf", &latitude);

		printf("경도를 입력해 주세요(실수형): ");
		scanf_s("%lf", &longitude);

		printf("위도: %f / 경도: %f\n", latitude, longitude);	
		printf("=======================================\n");
		printf(" 생성된 좌표의 구글 맵 링크: ");
		printf(" https://www.google.com/maps/search/?api=1&query=%f,%f\n", latitude, longitude);
		printf("생성된 좌표의 구글 어스 링크: ");
		printf("https://earth.google.com/web/@%f,%f,19000a\n", latitude, longitude);
		printf("=======================================\n");
	} else if (select == 4) {

		double lat_min = -90.0;
		double lat_max = 90.0;
		latitude = lat_min + (double)rand() / RAND_MAX * (lat_max - lat_min);

		double lon_min = -180.0;
		double lon_max = 180.0;
		longitude = lon_min + (double)rand() / RAND_MAX * (lon_max - lon_min);

		printf("위도: %f / 경도: %f\n", latitude, longitude);
		printf("=======================================\n");
		printf(" 생성된 좌표의 구글 맵 링크: ");
		printf(" https://www.google.com/maps/search/?api=1&query=%f,%f\n", latitude, longitude);
		printf("생성된 좌표의 구글 어스 링크: ");
		printf("https://earth.google.com/web/@%f,%f,19000a\n", latitude, longitude);
		printf("=======================================\n");
	} else {

		printf("잘못된 값\n");
	}

	char url[256];
	snprintf(url, sizeof(url), "https://nominatim.openstreetmap.org/reverse?format=json&lat=%f&lon=%f&accept-language=en", latitude, longitude);

	struct MemoryStruct chunk;
	chunk.memory = malloc(1);
	chunk.size = 0;

	CURL* curl = curl_easy_init();
	if (curl) {

		CURLcode res;

		curl_easy_setopt(curl, CURLOPT_URL, url);

		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "User-Agent: RandomGeoApp/1.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallBack);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {

			printf("CURL 통신 실패: %s\n", curl_easy_strerror(res));
		} else {

			char* name_start = strstr(chunk.memory, "\"display_name\":\"");
			if (name_start) {
				name_start += 16;
				char* name_end = strchr(name_start, '"');
				if (name_end) {
					*name_end = '\0';
					printf("\n=======================================\n");
					printf("찾은 위치: %s\n", name_start);
					printf("=======================================\n");
				}
			} else {

				printf("\n(이 좌표는 구체적인 주소 정보가 없는 지역입니다: 바다 또는 오지)\n");
			}
		}

		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
	}

	free(chunk.memory);

	return 0;
}