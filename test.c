#include <stdio.h>
#include <stdlib.h>
 
#include <string>
 
#include "include\config.h"
#include "include\lea.h"
 
#include "KISA_SHA256.h"
 
 
unsigned char mk[32] = { 0, };
 
unsigned int mk_len = 32;
 
char ctr_enc[16] = { 0, };
 
unsigned char pyn_buffer[16] = { 0, };
//unsigned int pyn_buffer_len = 16;
 
char cyp_buffer[16];
//unsigned int cyp_buffer_len = 16;
 
int main()
{
    size_t M = 0;
 
    SHA256_INFO sha256info;
 
    LEA_KEY key;
 
    FILE *fip = NULL;
    FILE *fop = NULL;
 
    //fip = fopen64("test", "rb");
    //fop = fopen64("test.LEA_CTR", "wb");
 
    fopen_s(&fip, "test", "rb");
    fopen_s(&fop, "test.lea", "wb");
 
    if (fip == NULL)
    {
        return -1;
    }
 
    if (fop == NULL)
    {
        return -1;
    }
    
    char password[256]="TestMessage";
 
    SHA256_Init(&sha256info);
    SHA256_Process(&sha256info, (unsigned char*)password, strlen(password));
 
    SHA256_Close(&sha256info, mk);
 
    lea_set_key(&key, mk, mk_len);
 
    M = fread(pyn_buffer, sizeof(char), sizeof(pyn_buffer), fip);
    lea_ecb_enc((unsigned char*)cyp_buffer, pyn_buffer, M, &key);
 
    if (fwrite(cyp_buffer, sizeof(char), M, fop) == 0)
    {
        fclose(fip);
        fclose(fop);
        _unlink("test.lea"); // 에러난 파일 지우고 종료
        return -1;
    }
 
    strcpy(ctr_enc, cyp_buffer);
 
    while ((M = fread(pyn_buffer, sizeof(char), sizeof(pyn_buffer), fip)) != NULL)
    {
        lea_ctr_enc((unsigned char*) cyp_buffer, pyn_buffer, M, (unsigned char*)ctr_enc, &key);
        //lea_ctr_dec(cyp_buffer, pyn_buffer,M,ctr_enc,&key);
        if (fwrite(cyp_buffer, sizeof(char), M, fop) == 0)
        {
            fclose(fip);
            fclose(fop);
            _unlink("test.lea"); // 에러난 파일 지우고 종료
            return -1;
        }
        //lea_ctr_enc(cyp_buffer, pyn_buffer, pyn_buffer_len, ctr_enc, &key);
        //fwrite(cyp_buffer, cyp_buffer_len, 1, fop);
    }
 
    fclose(fip);
    fclose(fop);
 
    return 0;
}
