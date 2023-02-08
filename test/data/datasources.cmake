cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_seq_ref.fasta
                URL_HASH SHA256=24d5bf54edf054b7407a0bc4707b72383b9467c051839a6cbd8ec8e2b6bb65f9)
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
declare_datasource (FILE 0_0_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400.stdout
                URL_HASH SHA256=fe8de850e54c784510666f1e065282ead64743a7a10f95fec6c43375c4dbb9e9)
declare_datasource (FILE 0_178_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_178_300.stdout
                URL_HASH SHA256=3ecaf2b976cd2630d33dd3f4f07aa449fe3bb08a6d6f64caec76a34b2a85c072)
declare_datasource (FILE 0_179_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_179_300.stdout
                URL_HASH SHA256=d6f565ce5a81ad1a1a58ea2664d586f07fbecc569022d7953dc5a96a64352c97)
declare_datasource (FILE 0_270_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_270_400.stdout
                URL_HASH SHA256=7c01302f37777e313f97b499313592ada3abce27050a3af2467c9a9af29f36ed)
declare_datasource (FILE 0_271_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_271_400.stdout
                URL_HASH SHA256=f439be137d776b70d5a83d728437bd6e441f216deb47e0b5c6fb5d08a2fa220e)
declare_datasource (FILE 0_341_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_341_450.stdout
                URL_HASH SHA256=eaab577e1ba83cc10c06498b4d0b07518abef0003e9f88c077e8ef8719459832)
declare_datasource (FILE 0_342_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_342_450.stdout
                URL_HASH SHA256=a159add1e93182da469a9022b13e3c47cb0e3fed0f5627547b571c7dace12105)
declare_datasource (FILE 0_500_643.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_643.stdout
                URL_HASH SHA256=b95126a46938af9451a2168965c39335613e388dec3fffa196d6bb5682d93f90)
declare_datasource (FILE 0_500_644.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_644.stdout
                URL_HASH SHA256=1ce2ccc164e7c5441d6b8abe67b6b932a76e120d7df4328c74c9b4a5ddb42e5d)
declare_datasource (FILE 0_600_721.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_721.stdout
                URL_HASH SHA256=9edfdf284164ebd3a203157f4fcbbe3b893b3eab81a41a8e217941452e533cde)
declare_datasource (FILE 0_600_722.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_722.stdout
                URL_HASH SHA256=23bb40c9b90dcc6a36be350882dccec12f5d4c223ce8cb4a9d3cea38766b3212)
declare_datasource (FILE 0_600_762.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_762.stdout
                URL_HASH SHA256=5a18b4495e73ef16256b3b4fa4e656b28b44f249f1efb9c91c33464fabffe03f)
declare_datasource (FILE 0_600_763.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_763.stdout
                URL_HASH SHA256=66173a9795e1779f753a47daa8f4b69a11bffbbe58a76f3faddb0c4a81d6043b)
declare_datasource (FILE full.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/full.stdout
                URL_HASH SHA256=6fce12cb3bab0baa51fa7180f5c946ee24b28b05f435472d64386dd80cf42a3b)
