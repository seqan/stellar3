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
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_178_300.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_178_300.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_179_300.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_179_300.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_270_400.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_270_400.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_271_400.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_271_400.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_341_450.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_341_450.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_342_450.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_342_450.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_500_643.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_643.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_500_644.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_644.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_600_721.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_721.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_600_722.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_722.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_600_762.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_762.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_600_763.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_763.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/full.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE out.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/out.gff
                URL_HASH SHA256=0f34bf94de7aedf306c69a91720bb09e2c8b89b7a8274d5eb77ea6fc2669d6db)
declare_datasource (FILE 0_0_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400.stdout
                URL_HASH SHA256=9efd3a23a4b68467ab01d27393a096c62a93525ae640a58854db64697d1fb290)
declare_datasource (FILE 0_178_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_178_300.stdout
                URL_HASH SHA256=ec32ae00957108ae58895bb3fd1fc44e480a94444a6f995c64c3dbd5be65f363)
declare_datasource (FILE 0_179_300.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_179_300.stdout
                URL_HASH SHA256=3b19bcc0e10a9b03d0bc19044c0a8f2c0ffa511828696e8dda03ee9e4d32dfcf)
declare_datasource (FILE 0_270_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_270_400.stdout
                URL_HASH SHA256=77deee174d27a561e6eff0de8b3131b2ff47735660bb1e612c7a954044786f47)
declare_datasource (FILE 0_271_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_271_400.stdout
                URL_HASH SHA256=529017478f4f757f0981829719bed4fdd59226475c59d5b4d7d03ef1becb861b)
declare_datasource (FILE 0_341_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_341_450.stdout
                URL_HASH SHA256=20eb812a83b41d73dbcaee09e4209e80fd91fce4f6bd73f6521e752dd1d33c3e)
declare_datasource (FILE 0_342_450.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_342_450.stdout
                URL_HASH SHA256=8ec13f6d3a9e5afa17657769e399c68bab3ccafa6f704f672d8a3670bb19cfcd)
declare_datasource (FILE 0_500_643.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_643.stdout
                URL_HASH SHA256=ed7af65f752049364bbd636cdda829c3344eabfbddfe54701a4000baea2dc63d)
declare_datasource (FILE 0_500_644.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_644.stdout
                URL_HASH SHA256=a0a192f32a6e55ac3db064142ddc1e813a88fa9c92fd177c168af7f5d0a52942)
declare_datasource (FILE 0_600_721.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_721.stdout
                URL_HASH SHA256=2aba795e5a79fae61bae91b7f2e18bf322b22dfe0b6a8ae2b4214f55916d2ba5)
declare_datasource (FILE 0_600_722.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_722.stdout
                URL_HASH SHA256=65d8539b32785bba8f23b101025ee614ba1aca8ff20ac14b935e206f8b9064af)
declare_datasource (FILE 0_600_762.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_762.stdout
                URL_HASH SHA256=11fa5d2f007e69edbc81c842d5b2ab72205341e92596e0959f310d0d8c6daf31)
declare_datasource (FILE 0_600_763.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_600_763.stdout
                URL_HASH SHA256=585b08741eca3ccb8ab7ed5656829233057b481bd9bf308300786aee95eba932)
declare_datasource (FILE full.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/full.stdout
                URL_HASH SHA256=d8921e0fe8cdb493de3e769349d84e346f778a2f363b1b851aec9f897f3d5819)
