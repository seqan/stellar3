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
declare_datasource (FILE 0_1_2_.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_2_.gff
                URL_HASH SHA256=6a073b53e85d4e099dd3f875e1257fbccce866e5738763729818e6297c7cb4be)
declare_datasource (FILE 0_178_300.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_178_300.gff
                URL_HASH SHA256=1d5be39356d6350803f3bc848df83d532cd5024d2740ffd7df27b9901c73c497)
declare_datasource (FILE 0_179_300.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_179_300.gff
                URL_HASH SHA256=db013fb9ab7701b9d57c91267935c888c02d76951f81d52be5324645dff67338)
declare_datasource (FILE 0_1_.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_.gff
                URL_HASH SHA256=be6ac6369a0b8999f6b4ddff7e81eefa606c96495374b4a017064a0d5b510fa3)
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
declare_datasource (FILE 1_2_.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/1_2_.gff
                URL_HASH SHA256=4e90415e2f1342f1e7f1b2f68b17bc373414eb24893dbabc7ea0f92b4eb1c9ef)
declare_datasource (FILE 1_.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/1_.gff
                URL_HASH SHA256=f87fd8fe4911cd574ec7d53579ff1916eb21be64e8eb040ff5b78c2c61ecc19a)
declare_datasource (FILE full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/full.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE multi_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_all.gff
                URL_HASH SHA256=6a073b53e85d4e099dd3f875e1257fbccce866e5738763729818e6297c7cb4be)
declare_datasource (FILE 0_0_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400.stdout
                URL_HASH SHA256=2ca416759a2bd658f73b16e3982e0eb1b5b33ffbf907d579a04037f46c732b0a)
declare_datasource (FILE 0_1_2_.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_2_.stdout
                URL_HASH SHA256=581653554575acf7ad5055b2dab8c9665f035d7f06b8a4c0cba7d14f16059a59)
declare_datasource (FILE 0_178_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_178_300.stdout
                URL_HASH SHA256=32635d6acdeef64b077d5d0f7e6e0ec3776e30d4cf7f0c27c1101b18f5b9b529)
declare_datasource (FILE 0_179_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_179_300.stdout
                URL_HASH SHA256=114b91f4532de36e91098291dd4f8d4d3f59460fb4ac5959b0680c287080d962)
declare_datasource (FILE 0_1_.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_.stdout
                URL_HASH SHA256=5f7f06a1d888be6285111441e7762ca8cdbfaf8aea0f8caedb0c6aa7877a41a4)
declare_datasource (FILE 0_270_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_270_400.stdout
                URL_HASH SHA256=d936d0a7793bb94f8dfb8be7b2146c536fe93b0a9b1122a6d6ca759621b0b9d8)
declare_datasource (FILE 0_271_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_271_400.stdout
                URL_HASH SHA256=d9f1240020f3aae3d8c125ff47bb8425855b43ad7c7cbffbcfcd86d30295ffea)
declare_datasource (FILE 0_341_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_341_450.stdout
                URL_HASH SHA256=71e4558e2280527736b56667fe9b2be4979e2551ed5ad98979acdabfc3fcb687)
declare_datasource (FILE 0_342_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_342_450.stdout
                URL_HASH SHA256=87942d88b85f78e7ea1ebf4b30e825930338318ac801d7038994c3df5635c663)
declare_datasource (FILE 0_500_643.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_643.stdout
                URL_HASH SHA256=c84a9d99f35c614467c7c7368401bbfb9eb6d6a1db419e3858abb93d7f1e2eac)
declare_datasource (FILE 0_500_644.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_644.stdout
                URL_HASH SHA256=fbe0ae26e042adc10b888d230b21dd06d8a266b9b601b661ebf93d86ce3a5490)
declare_datasource (FILE 0_600_721.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_721.stdout
                URL_HASH SHA256=f2c93d0223f36ddb5da6d6fa3cf48f1855d8c46e9b27e526a32315995b0a9e57)
declare_datasource (FILE 0_600_722.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_722.stdout
                URL_HASH SHA256=eec5019a7bf9d92f8baacc3293dea0c275f5195af78e3d983fa033f92a6bde56)
declare_datasource (FILE 0_600_762.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_762.stdout
                URL_HASH SHA256=a5398fbf98347fbe1d8cffd4a04e102cc23120ea1969d38fcd573558d8852dce)
declare_datasource (FILE 0_600_763.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_763.stdout
                URL_HASH SHA256=d4a35ce293ba6e4c4699e9a326f527d8087e7bced4435ff4e91b099637a19749)
declare_datasource (FILE 1_2_.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/1_2_.stdout
                URL_HASH SHA256=af9968de1446672d3b9ac40648e17f7792c65d515b63caca82ee58bf657f6288)
declare_datasource (FILE 1_.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/1_.stdout
                URL_HASH SHA256=39f8f432ed81182c87048e62aca7e7d494725d57e19f69918a887591e1cfc4cd)
declare_datasource (FILE full.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/full.stdout
                URL_HASH SHA256=d8921e0fe8cdb493de3e769349d84e346f778a2f363b1b851aec9f897f3d5819)
declare_datasource (FILE multi_all.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_all.stdout
                URL_HASH SHA256=c1561208f6bfb2a29748da9cd2be41bc036b04016b89ce594ef10f130be52ef3)
