#include "src/lea.h"
#include "src/lea_locl.h"

#include "benchmark.h"
#include "lea_benchmark.h"
#include "lea_vs.h"

#include <stdio.h>

#include "src/lea.h"
#include "src/lea_locl.h"

#include "benchmark.h"
#include "lea_benchmark.h"
#include "lea_vs.h"

#include <stdio.h>

/*
입력된 마스터키를 이용하여 라운드 키를 계산하고 LEA_KEY 구조체를 생성한다.
LEA_KEY 구조체는 마스터키 길이 정보와 라운드 키를 포함한다. LEA_KEY 구조체는 사용자가 선언한 후 입력해야 하며
초기화하지 않은 구조체의 주소를 입력해도 정상 동작한다.
*/

void lea_set_key(	// LEA 라운드 키 생성
	LEA_KEY* key,		//LEA 라운드 키와 라운드 수 정보를 가진 LEA_KEY 구조체의 주소
	const unsigned char* mk,	// 마스터 키
	unsigned int mk_len		// 마스터키의 길이 (입력 값으로 16, 24, 32만 가능)
);

/*
입력된 평문을 ECB 모드를 이용해 암호화한다.
*/

void lea_ecb_enc(		//입력된 평문을 ECB 모드로 암호화
	unsigned char* ct,		//암호문
	const unsigned char* pt,		//암호화하려는 평문
	unsigned int pt_len,		//평문의 길이 (16의 배수 길이만 입력가능)
	const LEA_KEY* key		//lea_set_key 함수를 통해 설정된 LEA_KEY 구조체의 주소
);




 int main(void)
{
	int ret;
	printf("SIMD: %s\n", get_simd_type());		// SIMD Type 출력
	if (ret = lea_mmt_ecb_test())	printf("LEA ECB FAIL(%d)\n", ret);

	lea_key_benchmark();
	lea_ecb_benchmark();

	return 0;
}
