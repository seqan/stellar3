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
declare_datasource (FILE 0_200_600.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_200_600.gff
                URL_HASH SHA256=dbd9162955ea4491280f3e8f39f257684390191d8ba47ab335e6f9efd086fe01)
declare_datasource (FILE 0_400_700.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_400_700.gff
                URL_HASH SHA256=09d84e455974bf980d2c9a1926ff79f5b1d5b5c7185e81173e974ca524ecbfb6)
declare_datasource (FILE full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/full.gff
                URL_HASH SHA256=494c5eb171f65cab949ac0ae84c78160f4f4ef88a1164a4fb6641e52f08058f5)
declare_datasource (FILE 0_0_400.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400.stdout
                URL_HASH SHA256=253c29ee81527a20429d18440c5b6493abaa51bbe441e8a45a756b2db99c46e8)
declare_datasource (FILE 0_200_600.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_200_600.stdout
                URL_HASH SHA256=9666a89fc809fcaf495eaf06c69b26292379be59bdd3ed37351a950328c1a262)
declare_datasource (FILE 0_400_700.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_400_700.stdout
                URL_HASH SHA256=6fc0a97f9c0d01fe0687da74e09dc6c54c01cee35caa6d6265c7323a8283ff4b)
declare_datasource (FILE full.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/full.stdout
                URL_HASH SHA256=d62e78e79020a342d34980212ed161083c54851251100d1bbe598cf2877ab9c0)
