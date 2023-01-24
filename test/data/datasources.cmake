cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_seq_ref.fasta
                URL_HASH SHA256=485269926182c713586341c0b71a4a5565b36b0e2cacb8b1e0b919389b407d19)
declare_datasource (FILE query_e0.05.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/query_e0.05.fasta
                URL_HASH SHA256=b107238db9e0c0515b33fff570a787a86126789a0341bd2fdb52c6c607772f8d)
declare_datasource (FILE ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/ref.fasta
                URL_HASH SHA256=1a616b3f60306dcde1f512871fb1968fde0d8ce3ac424c06bda57623fbb7dcc9)
declare_datasource (FILE 0_0_400.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400.gff
                URL_HASH SHA256=f3a549adb198df11fa20159efb11a28bdd50967d2cd374b08352b7174650b2d9)
declare_datasource (FILE 0_178_300.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_178_300.gff
                URL_HASH SHA256=1d5be39356d6350803f3bc848df83d532cd5024d2740ffd7df27b9901c73c497)
declare_datasource (FILE 0_179_300.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_179_300.gff
                URL_HASH SHA256=db013fb9ab7701b9d57c91267935c888c02d76951f81d52be5324645dff67338)
declare_datasource (FILE 0_270_400.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_270_400.gff
                URL_HASH SHA256=ac8a7bd1b42813c23a1dc05c256a5f0a2d8f4231a895590fb60c2b7ffea1d332)
declare_datasource (FILE 0_271_400.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_271_400.gff
                URL_HASH SHA256=5c1d168cac5b88b945d9f80181590dcd8bf073643f57e249e67d79971f9b7c78)
declare_datasource (FILE 0_341_450.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_341_450.gff
                URL_HASH SHA256=5c1d168cac5b88b945d9f80181590dcd8bf073643f57e249e67d79971f9b7c78)
declare_datasource (FILE 0_342_450.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_342_450.gff
                URL_HASH SHA256=fc2d75bb965b47e6fda263b37e47f3df98179c7ee723e09e2451efb0b8e1426b)
declare_datasource (FILE 0_500_643.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_643.gff
                URL_HASH SHA256=57fc536ff726f56c86e67567eed7380a9b44e19de8225dd0eb1e79f680850974)
declare_datasource (FILE 0_500_644.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_644.gff
                URL_HASH SHA256=273c6b0a4b9b542af6900cc4f7bc2add227a9c41183c43163e584b21172b8f12)
declare_datasource (FILE 0_600_721.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_721.gff
                URL_HASH SHA256=4296c6d34980c1fdeed1cf62d1c433d6f01a1878452efd709e22c95bf3463844)
declare_datasource (FILE 0_600_722.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_722.gff
                URL_HASH SHA256=337792edd382c2e9fba2f8445231179fd4d643b106bdf2df0f8eb91152337591)
declare_datasource (FILE 0_600_762.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_762.gff
                URL_HASH SHA256=1567675ac591ec25fca4a3c76ecbaf114eeed646c48d1a1522bb7425e77f0271)
declare_datasource (FILE 0_600_763.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_763.gff
                URL_HASH SHA256=d7c21c7211ed9b1ca5439efbefd22e7341e6227601994a79fa120b779e53761c)
declare_datasource (FILE full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/full.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE out.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/out.gff
                URL_HASH SHA256=8cb13f833d3d0b417b82ac393b83610c439774f6fca5d1ef90e63dad44ca7986)
declare_datasource (FILE 0_0_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400.stdout
                URL_HASH SHA256=fe20a762924dd3253a7176f9df76f1df462836fc0f12587b0aa5762af5a990b5)
declare_datasource (FILE 0_178_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_178_300.stdout
                URL_HASH SHA256=15ce05dad04f8f5c030030ef1100fa25527c640c9d3f8fbac5b06b974f07250f)
declare_datasource (FILE 0_179_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_179_300.stdout
                URL_HASH SHA256=d106879b6d726310102a2a754ed37e1838b08746ba297267312d8f1da5bb8092)
declare_datasource (FILE 0_270_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_270_400.stdout
                URL_HASH SHA256=944fce345b3cbf43abc060b643b3dcabc67d72c3ad9be61e1a30a8129d4870c9)
declare_datasource (FILE 0_271_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_271_400.stdout
                URL_HASH SHA256=3cb4cf5bea64ab1216b4828116e0816514ebba07977d7ae3ccdb75a0b801806f)
declare_datasource (FILE 0_341_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_341_450.stdout
                URL_HASH SHA256=81e30e176117dc15aa5c816c7e19876243f28752ca96cce6b00e2b1dde5c2d4c)
declare_datasource (FILE 0_342_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_342_450.stdout
                URL_HASH SHA256=bbd9752e44ee4a75738d8bc1c956fe652c2d4ee6ab9e802f1ca604dc207e22f6)
declare_datasource (FILE 0_500_643.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_643.stdout
                URL_HASH SHA256=00fe876b86b7ec3a28011c6fb5ce52412eca992f95c2d2aba01b26d049005c5f)
declare_datasource (FILE 0_500_644.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_644.stdout
                URL_HASH SHA256=8883694b7a998f61c0607489e054a8e0f9f3185f7937cefa07a693a06a47fd91)
declare_datasource (FILE 0_600_721.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_721.stdout
                URL_HASH SHA256=c610580b5b67e09cbda903785bf541a8085df2e54cf8d0c814cf6053934682f9)
declare_datasource (FILE 0_600_722.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_722.stdout
                URL_HASH SHA256=0f0da67f0d5cb670ea23ced77f9ae565edf570b2229d86f0b65c261e4f092d08)
declare_datasource (FILE 0_600_762.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_762.stdout
                URL_HASH SHA256=991068552c5fd29a184d723fc68338996225da36e75e929390732e85ba9f814a)
declare_datasource (FILE 0_600_763.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_763.stdout
                URL_HASH SHA256=51abc931c24783a32b7b87c3fe14a5bf960a3c50b2a71563c22bc936ba9c04e8)
declare_datasource (FILE full.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/full.stdout
                URL_HASH SHA256=2aadbb5058889ba4afc88f98f4a2dfb15d7609d584b41aadf03b04783b17960c)
