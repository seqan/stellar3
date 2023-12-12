cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_seq_ref.fasta
                URL_HASH SHA256=c91e4b0aee16c0a8a9db0507cc12e15241aeaa1db8e065f7cb117991f7a7ac2a)
declare_datasource (FILE query_e0.0009.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/query_e0.0009.fasta
                URL_HASH SHA256=1ad1a3d42c801b6518d23ff193b0002da316a290eedde84c96a2ea27693fdc51)
declare_datasource (FILE query_e0.05.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/query_e0.05.fasta
                URL_HASH SHA256=5c055b271113473970757db3e313353906b387a46424a88bc137e7948d10066d)
declare_datasource (FILE query_e0.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/query_e0.fasta
                URL_HASH SHA256=ba532bf5c9e061bc55c2896a3eb62a2fa66fd0ecd166c64d038b803876a29f48)
declare_datasource (FILE ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/ref.fasta
                URL_HASH SHA256=164711f40cc09a4185a1249fbe5fcbd37049a447dad12d6f1562e910e8615c08)
declare_datasource (FILE 0_0_400_0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400_0.05.gff
                URL_HASH SHA256=ffab7e7f20e0b6e503cdde799a1e06609d91a6a35223326b86ec8c8f07d4d9e9)
declare_datasource (FILE 0_0_400_0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400_0.gff
                URL_HASH SHA256=1edec71b73c451ec2694b486166bd72f95b99fe20e85e5be140a88b0829f9042)
declare_datasource (FILE 0_1_0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_0.05.gff
                URL_HASH SHA256=95dae6f338266952f6b9d6aeb2c62347c7c43b3e2138e7ae2e0b839547a122d6)
declare_datasource (FILE 0_1_0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_0.gff
                URL_HASH SHA256=cec48374f0094b7553356b9c662150126eb9a9fdf80fb147a162af6ebdfd9e9f)
declare_datasource (FILE 0_1_2_0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_2_0.05.gff
                URL_HASH SHA256=95dae6f338266952f6b9d6aeb2c62347c7c43b3e2138e7ae2e0b839547a122d6)
declare_datasource (FILE 0_1_2_0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_2_0.gff
                URL_HASH SHA256=4de36c19a71a200cca9bdfd17505076394aeb98efda1206773e5e87a885759b4)
declare_datasource (FILE 0_500_800_0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_800_0.05.gff
                URL_HASH SHA256=5a1319cd3704e9ea6da0f37711a95647d44db09cb69431a3ed508bde145fb8ad)
declare_datasource (FILE 0_500_800_0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_800_0.gff
                URL_HASH SHA256=33361a21310ee461e507d65642dd33f3ac1e7dbd064bc1890efddb468bb6bb9d)
declare_datasource (FILE 1_0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/1_0.05.gff
                URL_HASH SHA256=8588f387723d77073b4c3d18ad60ab715950e206b9e6288854ed17b950b2db14)
declare_datasource (FILE 1_0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/1_0.gff
                URL_HASH SHA256=2fac598ed9e83eb8a525c4c643a0805ae9baeec55b0af12f864efd91b8159b2c)
declare_datasource (FILE 1_2_0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/1_2_0.05.gff
                URL_HASH SHA256=8588f387723d77073b4c3d18ad60ab715950e206b9e6288854ed17b950b2db14)
declare_datasource (FILE 1_2_0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/1_2_0.gff
                URL_HASH SHA256=e000a5c3b53539126c336a03e2216cc5bdcebdaa768463c684ad323d38144d19)
declare_datasource (FILE edge_case_e0.0009.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/edge_case_e0.0009.gff
                URL_HASH SHA256=ce7648a8aa6496624c491ee899ce1ff8e00abe244383352d1e8425c36c4592fb)
declare_datasource (FILE edge_case_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/edge_case_e0.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE full_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/full_e0.05.gff
                URL_HASH SHA256=565adf028b7ad81af650b5077fb6d882401cd441763c78f3f12912998643d53f)
declare_datasource (FILE full_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/full_e0.gff
                URL_HASH SHA256=f2bd978006259862b953dc1a2d2a8d052cf936fc68f7303ee8a0126ea93f8fd7)
declare_datasource (FILE multi_all_0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_all_0.05.gff
                URL_HASH SHA256=95dae6f338266952f6b9d6aeb2c62347c7c43b3e2138e7ae2e0b839547a122d6)
declare_datasource (FILE multi_all_0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_all_0.gff
                URL_HASH SHA256=4de36c19a71a200cca9bdfd17505076394aeb98efda1206773e5e87a885759b4)
declare_datasource (FILE 0_0_400_0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400_0.05.stdout
                URL_HASH SHA256=6b5c650c1612f806969b2bb258100b31dd6a9ffa2a774b19fdaba5c2e61dd32e)
declare_datasource (FILE 0_0_400_0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_0_400_0.stdout
                URL_HASH SHA256=c4613d76d95a48e979b7d9ab7cf2a5b49dac926381157df21af51210a5f69375)
declare_datasource (FILE 0_1_0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_0.05.stdout
                URL_HASH SHA256=865bb8e5afa44a8ef303f5e84d9f79f4677725ee77f550399a75553b34e30577)
declare_datasource (FILE 0_1_0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_0.stdout
                URL_HASH SHA256=1deada2e1880b3b7216129986e9c8af5b88ee1a9e470bb969a9599b4074cb7b3)
declare_datasource (FILE 0_1_2_0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_2_0.05.stdout
                URL_HASH SHA256=4ff9ac7def50d94ea52f1758a77236abf7f8b8c4a240960df0ea23d1e0985024)
declare_datasource (FILE 0_1_2_0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_1_2_0.stdout
                URL_HASH SHA256=a9ffd7ec18827eda9a1bb0354ecefea9c1a40fc35a832769c4adecd54ecdb324)
declare_datasource (FILE 0_500_800_0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_800_0.05.stdout
                URL_HASH SHA256=c9f1784b6f1b7c880fca8f72794c3b6b1c9162c0799b4b75ec33a596b90f11f8)
declare_datasource (FILE 0_500_800_0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/0_500_800_0.stdout
                URL_HASH SHA256=e0e6deba9aa30d5052f114d81b8a07184a9a11895992be9c3cc1ecdbd2b95080)
declare_datasource (FILE 1_0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/1_0.05.stdout
                URL_HASH SHA256=e4ecf01ce25fdaead0e0ceea5a366142603f3c02700f23d93c1ccc4970d54c4f)
declare_datasource (FILE 1_0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/1_0.stdout
                URL_HASH SHA256=96ae774a74bf34beb830468da897851fbfa5e18a7dc7fdffaf9995bcda1d0cd9)
declare_datasource (FILE 1_2_0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/1_2_0.05.stdout
                URL_HASH SHA256=5556fb5c219d734550c5a2490ed309ef64e4f853e3ba8812e5d65b16969e9212)
declare_datasource (FILE 1_2_0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/1_2_0.stdout
                URL_HASH SHA256=9f2761571503673e5c86ede09b8735688ef0251e18280d02b27a6392a3b274e4)
declare_datasource (FILE edge_case_e0.0009.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/edge_case_e0.0009.stdout
                URL_HASH SHA256=92814aa6a23fdf4941a12568eb6ce4651fbd10eef1f4022ebf75832b7614660d)
declare_datasource (FILE edge_case_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/edge_case_e0.stdout
                URL_HASH SHA256=986241ff98a61099fb9f8a700e66bcdadfd6e9fcdaf121e86e5720a5e858d4c7)
declare_datasource (FILE full_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/full_e0.05.stdout
                URL_HASH SHA256=e3e7a638e15f8cefa2e60c1bb25ef3b89d11bbdfde08a9534a9104e03788e522)
declare_datasource (FILE full_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/full_e0.stdout
                URL_HASH SHA256=29cd687e562b83e11d671936d1cce445952a3a863abb1fa0ac14ecb445ae0059)
declare_datasource (FILE multi_all_0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_all_0.05.stdout
                URL_HASH SHA256=1e60c69455939920b5b36fec464005ef95ca6be284c1a6aa74274ffaa846846b)
declare_datasource (FILE multi_all_0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_all_0.stdout
                URL_HASH SHA256=294a8b6a4f5ed9add3df66a38a7e98cbd62d2c57f82462425c282170ce74600c)
