#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aktool.h"
#include <libakrypt.h>

#include "ak_mac.c"

#ifdef AK_HAVE_ERRNO_H
#include <errno.h>
#endif
#ifdef AK_HAVE_SYSSTAT_H
#include <sys/stat.h>
#endif

int aktool_digsign_help( void ){
    printf(
            _("aktool ds -s [filename of secret key] -d [filename of document] - digital signature for file generation \n\n"));
    printf(
            _("aktool ds -s [filename of secret key] -v [filename of document] - verifying digital signature for file\n\n"));
    /*printf(
            _("aktool key [options]  - key generation and management functions\n\n"));
    printf(
            _(" -n, --new               generate a new key or key pair for specified target\n"),
            aktool_default_generator);*/
    printf(
            _("options used for customizing a public key's certificate:\n"));
    aktool_print_common_options();

    printf(_("for usage examples try \"man aktool\"\n" ));

    return EXIT_SUCCESS;
}
/*
typedef struct {
    int errcount;
    ak_ecies_scheme sheme;
    ak_pointer key;
} handle_ptr_t;*/


int digsign(int argc, tchar *argv[]){


    struct random gen;
    ak_random_create_lcg(&gen);

    ak_uint8 sign[128];
    struct signkey sk;
    struct signkey lk;
    struct verifykey vk;
    char filesig[128];
    char fileout[128];
    char signature[128];
    char filever[128];
    char filept[128];
    struct file ofp, aaa;

    int next_option = 0, exitcode = EXIT_FAILURE;
    enum {do_nothing, smth, create_sign, do_ver} work = do_nothing;
    const struct option long_options[] = {
            { "verify_file",                 1, NULL,  'v' },
            { "file",                 1, NULL,  'd' },
            { "signature",                 1, NULL,  's' },
            { "verify_key",                 1, NULL,  'p' }

    };
    do {
        next_option = getopt_long(argc, argv, "hs:d:v:p:", long_options, NULL);

        switch (next_option){

            case 's':
                ak_realpath( optarg , signature, sizeof( signature ) - 1 );
                break;

            case 'd':
                work = create_sign;
                strcpy(fileout, optarg);
                strcat(fileout, "-signf");
                ak_realpath( optarg , filesig, sizeof( filesig ) - 1 );
                break;

            case 'v':
                work = do_ver;
                strcpy(fileout, optarg);
                strcat(fileout, "-signf");
                ak_realpath( optarg , filever, sizeof( filever ) - 1 );
                break;

            case 'p':
                ak_realpath( optarg , filept, sizeof( filept ) - 1 );
                break;

            default:
                break;
        }
    } while( next_option != -1 );
    if( work == do_nothing ) return aktool_digsign_help();




    //ak_uint8 testkey[32] = {0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x27, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x28 };
    //ak_signkey_set_key(&sk, testkey, 32);

    //ak_signkey_create_str(&sk, "cspa");
    //ak_skey_export_to_file_with_password( &sk, "qwer", 4, filept, sizeof (filept), asn1_der_format );
    //ak_signkey_destroy( &sk );

    if( work == create_sign ) {
/*
        struct hash ctx;

        ak_uint8 out[32];
        ak_hash_create_streebog256( &ctx );
        size_t len ;
        //printf("%d\n", len);
        ak_hash_file( &ctx, filesig, out, len = ak_hash_get_tag_size( &ctx ));
        //printf("%s\n",ak_ptr_to_hexstr(out, len, ak_false));

        ak_signkey_sign_hash(&sk, &gen, out, len, sign, 128);
        printf("Электронная подпись: %s\n", ak_ptr_to_hexstr(sign, ak_signkey_get_tag_size(&sk), ak_false));

        if (verneed != 0) {
            ak_verifykey_create_from_signkey(&vk, &sk);
            printf("Проверка подленности: ");
            ak_hash_file(&ctx, filever, out, len = ak_hash_get_tag_size(&ctx));
            if (ak_verifykey_verify_hash(&vk, out, len, sign) == ak_true) { printf("ok\n"); }
            else { printf("not ok\n"); }
        }
*/

        if( ak_skey_import_from_file( &sk, sign_function, signature ) != ak_error_ok )
            return EXIT_FAILURE;

        ak_verifykey_create_from_signkey( &vk, &sk );

        ak_verifykey_destroy( &vk );

        ak_signkey_sign_file( &sk, &gen, filesig, sign, sizeof( sign ));

        ak_random_destroy( &gen );
        printf("Электронная подпись создана: %s...\n", ak_ptr_to_hexstr(sign, 8, ak_false));

        ak_file_create_to_write(&ofp, fileout);
        ak_file_write(&ofp, sign, 128);

        ak_signkey_destroy( &sk );

    }
    if( work == do_ver ) {
        if( ak_skey_import_from_file( &lk, sign_function, signature ) != ak_error_ok )
            return EXIT_FAILURE;

        ak_verifykey_create_from_signkey( &vk, &lk );

        ak_file_open_to_read(&aaa, fileout);
        ak_file_read(&aaa, sign, 128);

        printf("verify: ");
        if( ak_verifykey_verify_file( &vk, filever, sign )) printf("Ok\n\n");
        else { printf("Wrong\n\n"); }
    }



    //ak_file_write("resres", ak_ptr_to_hexstr(sign, ak_signkey_get_tag_size(&sk), ak_false), 128);
    //запись в файл res, пока не ясно как записать через ak_file_write или еще как
    /*char digsign[256];
    char ss[256*3/2];

    strncpy(digsign, ak_ptr_to_hexstr(sign, ak_signkey_get_tag_size(&sk), ak_false), 256);

    int j = 0;
    for(int i = 0; i < 256; i = i+2){
        ss[i+j] = digsign[i];
        ss[i+1+j] = digsign[i+1];
        ss[i+2+j] = ' ';
        j++;
    }

    char * filename1 = strcat(filesig, "res");
    FILE *fp;
    if((fp= fopen(filename1, "w"))==NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
    fputs(ss, fp);
    fclose(fp);
*/

/*
    ak_libakrypt_print_asn1("kuznec.key");
    ak_libakrypt_convert_asn1("kuznec.key", "kk", asn1_pem_format, secret_key_content);
    ak_libakrypt_split_asn1("kk",asn1_pem_format, secret_key_content);
    ak_libakrypt_print_asn1("kk-0000.pem");
    ak_asn1 root = NULL;
    ak_asn1_import_from_file(root = ak_asn1_new(), "kuznec.key", NULL);
    printf("%s", ak_ptr_to_hexstr(root->current, 32, ak_false));
*/

    //для txt
    /*
    ak_signkey_sign_file(&sk, &gen, filesig, sign, 128);
    printf("Электронная подпись: %s\n", ak_ptr_to_hexstr(sign, ak_signkey_get_tag_size(&sk), ak_false));
    if(verneed != 0) {
        ak_verifykey_create_from_signkey(&vk, &sk);
        printf("Проверка подленности: ");
        if (ak_verifykey_verify_file(&vk, filever, sign) == ak_true) { printf("ok"); }
        else { printf("not ok"); }
    }*/

    //для пдф
    /*
    size_t len = 0;
    struct hash ctx;
    ak_uint8 out[32];
    ak_hash_create_streebog256( &ctx );
    ak_hash_file( &ctx, filesig, out, len = ak_hash_get_tag_size( &ctx ));
    ak_signkey_sign_hash(&sk, &gen, out, 32, sign, 128);
    printf("Электронная подпись: %s\n", ak_ptr_to_hexstr(sign, ak_signkey_get_tag_size(&sk), ak_false));

    if(verneed != 0) {
        ak_verifykey_create_from_signkey(&vk, &sk);
        printf("Проверка подленности: ");
        ak_hash_file( &ctx, filesig, out, len = ak_hash_get_tag_size( &ctx ));
        if (ak_verifykey_verify_hash( &vk, out, 32, sign) == ak_true) { printf("ok\n"); }
        else { printf("not ok\n"); }
    }*/

    /*
    int error = ak_error_ok;
    ak_uint8 *tkey = NULL, buffer[32];
    size_t size = sizeof( buffer );

    struct bckey bkey, *lkey = NULL;
    ak_pointer key = NULL;

    if(( st.key = ak_skey_load_from_file( "/home/shvarev/456/libakrypt-0.x-master/cmake-build-debug/kuznec.key" )) == NULL ) {
        printf("sdf");
        return EXIT_FAILURE;
    }
    if( ak_error_get_value() != ak_error_ok ) {
        printf("Exit on error value! Pointer is'nt equal to NULL\n");
        return EXIT_FAILURE;
    }
*/

    //printf("Открытый ключ: %s\n", ak_ptr_to_hexstr(vk.number, 32, ak_false));

    /*
    int result = EXIT_SUCCESS;
    ak_oid curvoid = NULL;
    curvoid = ak_oid_find_by_mode( wcurve_params );
    ak_oid oid = NULL;
    ak_uint8 testkey[64] = {
            0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x27, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
            0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x38,
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
            0xf1, 0xe2, 0xd3, 0xc4, 0xb5, 0xa6, 0x97, 0x88, 0x79, 0x6a, 0x5b, 0x4c, 0x3d, 0x2e, 0x1f, 0x00 };

    char filename[128];
    char tname[256];
    struct signkey skey, lkey;
    struct verifykey vkey;
    struct random generator;

    ak_random_create_lcg( &generator );


    if(( curvoid->engine == identifier ) && ( curvoid->mode == wcurve_params )) {
        ak_signkey_create( &skey, (ak_wcurve)curvoid->data );
        ak_signkey_set_key( &skey, testkey, (((ak_wcurve)curvoid->data)->size << 3 ));
    } else return EXIT_FAILURE;
    printf("---- oid: %s (%s)\n", curvoid->id[0], curvoid->name[0] );

    ak_verifykey_create_from_signkey( &vkey, &skey );
    ak_verifykey_destroy( &vkey );

    printf("secret key number:\t%s\n",
           ak_ptr_to_hexstr( skey.key.number, sizeof( skey.key.number ), ak_false ));
    printf("subject key identifier:\t%s\n",
           ak_ptr_to_hexstr( skey.verifykey_number, sizeof( skey.verifykey_number ), ak_false ));


    ak_signkey_sign_ptr( &skey, &generator, filesig, 13, sign, sizeof( sign ));
    printf("signature: %s ... \n", ak_ptr_to_hexstr( sign, 8, ak_false ));
    ak_random_destroy( &generator );


    //ak_snprintf( tname, sizeof( tname ), "keylabel-%s-%03u", curvoid->name[0], skey.key.number[0] );
    //ak_skey_set_label( (ak_skey)&skey, tname, 0 );

    ak_skey_export_to_file_with_password( &skey,
                                          "password", 8, filename, sizeof( filename ), asn1_der_format );

    ak_signkey_destroy( &skey );


    if( ak_skey_import_from_file( &lkey, sign_function, filever ) != ak_error_ok )
        return EXIT_FAILURE;



    ak_verifykey_create_from_signkey( &vkey, &lkey );
    printf("  created key: %s\n", ak_ptr_to_hexstr( vkey.number, 32, ak_false ));
    printf("verify: ");
    if( ak_verifykey_verify_ptr( &vkey, filesig, 13, sign )) printf("Ok\n\n");
    else { printf("Wrong\n\n"); result = EXIT_FAILURE; }
*/

    return 0;
}
