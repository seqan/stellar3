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
                URL_HASH SHA256=937ddcb127bbce3da0649d854d3e052e214eef99dcb536b9b6e045e0864e8f20)
declare_datasource (FILE 0_178_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_178_300.stdout
                URL_HASH SHA256=5ba8b4bf79ed5070ce0f331194c0805572ca13496bb9ee53681191d269e8148a)
declare_datasource (FILE 0_179_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_179_300.stdout
                URL_HASH SHA256=f35d846ba6142ab23f67726d18cd81c16189a70ee5cb684d27263d210c7de4fb)
declare_datasource (FILE 0_270_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_270_400.stdout
                URL_HASH SHA256=d09777286c68b2c9516d5a9f54244fe18ea29ab75d7faa6556997dab426f6e0f)
declare_datasource (FILE 0_271_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_271_400.stdout
                URL_HASH SHA256=288c38fc17f6f6a47b5a498054368b43806a751237b19fc68be477f9e4f05872)
declare_datasource (FILE 0_341_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_341_450.stdout
                URL_HASH SHA256=63220155af9361e3b8be52b2b207ef3aca65d43f8b7c37c15a8ca5bbc6af0733)
declare_datasource (FILE 0_342_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_342_450.stdout
                URL_HASH SHA256=b5ad9c7bed57172840173c50b4193d58e1200b8ffc475e331db41aaadbdafeda)
declare_datasource (FILE 0_500_643.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_643.stdout
                URL_HASH SHA256=3fc46484ac17eb32310143400f23c319e3bd6c26ee66de3a20da5f55fb07f434)
declare_datasource (FILE 0_500_644.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_644.stdout
                URL_HASH SHA256=f070a412734926f73c9a8cfc8d832dd4a1d3dac5539c2f5ddd2e54eea861aa8c)
declare_datasource (FILE 0_600_721.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_721.stdout
                URL_HASH SHA256=74162fb31fab55fc349fe9d40723ad31fe6510e8dc17d8f9cb8301651f50ff0e)
declare_datasource (FILE 0_600_722.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_722.stdout
                URL_HASH SHA256=3c99a2e2bc00c8fb729f41758711c7fe5698e833fa4655816f92c2b2893633d5)
declare_datasource (FILE 0_600_762.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_762.stdout
                URL_HASH SHA256=6202d1f3e5d03f8d2eee63f12523cdb57be82bdabad617ea48c9b180014de259)
declare_datasource (FILE 0_600_763.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_763.stdout
                URL_HASH SHA256=b210e5a80d9357b13fb24b6c933ef7c2f967b2abc794642cdbec86e40007285b)
declare_datasource (FILE full.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/full.stdout
                URL_HASH SHA256=2aadbb5058889ba4afc88f98f4a2dfb15d7609d584b41aadf03b04783b17960c)
