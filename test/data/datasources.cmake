cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/multi_seq_ref.fasta
                URL_HASH SHA256=c91e4b0aee16c0a8a9db0507cc12e15241aeaa1db8e065f7cb117991f7a7ac2a)
declare_datasource (FILE query_e0.001.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/query_e0.001.fasta
                URL_HASH SHA256=5aa1989d674d0c0f23b44d001b22b167117b35ea8d5588270c76809d40e3386e)
declare_datasource (FILE query_e0.05.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/query_e0.05.fasta
                URL_HASH SHA256=5c055b271113473970757db3e313353906b387a46424a88bc137e7948d10066d)
declare_datasource (FILE query_e0.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/query_e0.fasta
                URL_HASH SHA256=ba532bf5c9e061bc55c2896a3eb62a2fa66fd0ecd166c64d038b803876a29f48)
declare_datasource (FILE ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/ref.fasta
                URL_HASH SHA256=164711f40cc09a4185a1249fbe5fcbd37049a447dad12d6f1562e910e8615c08)
declare_datasource (FILE subset_0_1_2_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/0_1_2_e0.05.gff
                URL_HASH SHA256=95dae6f338266952f6b9d6aeb2c62347c7c43b3e2138e7ae2e0b839547a122d6)
declare_datasource (FILE subset_0_1_2_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/0_1_2_e0.05.stdout
                URL_HASH SHA256=2a53e9b6b05da7e1dac002c03746e7f3d05ce0676d163aa5b57bc6debe52996b)
declare_datasource (FILE subset_0_1_2_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/0_1_2_e0.gff
                URL_HASH SHA256=4de36c19a71a200cca9bdfd17505076394aeb98efda1206773e5e87a885759b4)
declare_datasource (FILE subset_0_1_2_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/0_1_2_e0.stdout
                URL_HASH SHA256=bdf6f06f076916c07759d54280db8b1a7bf1f51aa435ca30eeb0c55328ceb51d)
declare_datasource (FILE subset_0_1_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/0_1_e0.05.gff
                URL_HASH SHA256=95dae6f338266952f6b9d6aeb2c62347c7c43b3e2138e7ae2e0b839547a122d6)
declare_datasource (FILE subset_0_1_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/0_1_e0.05.stdout
                URL_HASH SHA256=95d8d0b6ecb0351182ca9d11eba385ea3d8bd549683d6d4c9bff539484fba709)
declare_datasource (FILE subset_0_1_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/0_1_e0.gff
                URL_HASH SHA256=cec48374f0094b7553356b9c662150126eb9a9fdf80fb147a162af6ebdfd9e9f)
declare_datasource (FILE subset_0_1_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/0_1_e0.stdout
                URL_HASH SHA256=28e66ce35f3e35c022722ff1580a3ee224ac1e21d335f2bfa04b8ac5e8f8059b)
declare_datasource (FILE subset_1_2_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/1_2_e0.05.gff
                URL_HASH SHA256=8588f387723d77073b4c3d18ad60ab715950e206b9e6288854ed17b950b2db14)
declare_datasource (FILE subset_1_2_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/1_2_e0.05.stdout
                URL_HASH SHA256=2e931f0310bab350a6a332cdc0837dea8824c885a896d2ef12c68d1686445ea7)
declare_datasource (FILE subset_1_2_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/1_2_e0.gff
                URL_HASH SHA256=e000a5c3b53539126c336a03e2216cc5bdcebdaa768463c684ad323d38144d19)
declare_datasource (FILE subset_1_2_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/1_2_e0.stdout
                URL_HASH SHA256=32bc5adc1b589bb068e1f975d61513e52dacfae8dc6d10172616d3b81720b3bc)
declare_datasource (FILE subset_1_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/1_e0.05.gff
                URL_HASH SHA256=8588f387723d77073b4c3d18ad60ab715950e206b9e6288854ed17b950b2db14)
declare_datasource (FILE subset_1_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/1_e0.05.stdout
                URL_HASH SHA256=d5a36c582db7e89d99eebf2902917ccaade0cac8ca4ff78484a9f253e3151491)
declare_datasource (FILE subset_1_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/1_e0.gff
                URL_HASH SHA256=2fac598ed9e83eb8a525c4c643a0805ae9baeec55b0af12f864efd91b8159b2c)
declare_datasource (FILE subset_1_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/1_e0.stdout
                URL_HASH SHA256=6d6eccab76af1f33904c6d5c0cded0684fd96f5f87a870c7190d68d55dac44eb)
declare_datasource (FILE subset_all_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/all_e0.05.gff
                URL_HASH SHA256=95dae6f338266952f6b9d6aeb2c62347c7c43b3e2138e7ae2e0b839547a122d6)
declare_datasource (FILE subset_all_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/all_e0.05.stdout
                URL_HASH SHA256=255fbe413977dde97499cbae7a4305d89c820d889868a0a259bbc6dce98063bb)
declare_datasource (FILE subset_all_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/all_e0.gff
                URL_HASH SHA256=4de36c19a71a200cca9bdfd17505076394aeb98efda1206773e5e87a885759b4)
declare_datasource (FILE subset_all_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/subset/all_e0.stdout
                URL_HASH SHA256=252bdd6ff50a73d3e1a7354f66946fc934f0fa1ed0fc8fee3617a84a40ad6e44)
declare_datasource (FILE segment_0_0_400_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_0_400_e0.05.gff
                URL_HASH SHA256=ffab7e7f20e0b6e503cdde799a1e06609d91a6a35223326b86ec8c8f07d4d9e9)
declare_datasource (FILE segment_0_0_400_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_0_400_e0.05.stdout
                URL_HASH SHA256=06fc16af5d072bd77236832ddc395eea031b5256f0820a58e573f4b43c755030)
declare_datasource (FILE segment_0_0_400_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_0_400_e0.gff
                URL_HASH SHA256=1edec71b73c451ec2694b486166bd72f95b99fe20e85e5be140a88b0829f9042)
declare_datasource (FILE segment_0_0_400_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_0_400_e0.stdout
                URL_HASH SHA256=8bdbab126ef2e2fb2a6e7c417bfb713d60f7c0fa05dff522099524ac8556ccb5)
declare_datasource (FILE segment_0_500_800_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_500_800_e0.05.gff
                URL_HASH SHA256=5a1319cd3704e9ea6da0f37711a95647d44db09cb69431a3ed508bde145fb8ad)
declare_datasource (FILE segment_0_500_800_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_500_800_e0.05.stdout
                URL_HASH SHA256=d7ba016b3b02b09377b6a6a37d9d2e01d10f5ab97a35bbd6c82b7f03775fb8e6)
declare_datasource (FILE segment_0_500_800_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_500_800_e0.gff
                URL_HASH SHA256=76d780587daabf0361f1b3749d253583f17014039e49ecddcea278dc9a32f39d)
declare_datasource (FILE segment_0_500_800_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_500_800_e0.stdout
                URL_HASH SHA256=6ba74f2133356cfa83fc676e3d5d8f8134601fd2936037927a1da3acc3f38389)
declare_datasource (FILE segment_all_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/all_e0.05.gff
                URL_HASH SHA256=565adf028b7ad81af650b5077fb6d882401cd441763c78f3f12912998643d53f)
declare_datasource (FILE segment_all_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/all_e0.05.stdout
                URL_HASH SHA256=e850850a1f1369d6de572f75922a2cf874a7a4173921c1e9b2beb720d0bad494)
declare_datasource (FILE segment_all_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/all_e0.gff
                URL_HASH SHA256=f2bd978006259862b953dc1a2d2a8d052cf936fc68f7303ee8a0126ea93f8fd7)
declare_datasource (FILE segment_all_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/all_e0.stdout
                URL_HASH SHA256=b80181e12bbc619f1de49927eec44bac16e8fe994860f59c3971251086cfc443)
declare_datasource (FILE er_edge_case_e0.0009.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.0009.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE er_edge_case_e0.0009.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.0009.stdout
                URL_HASH SHA256=502671662ae997ba96068e6b000afb945a618fab622717574889598d2c5f2ffe)
declare_datasource (FILE er_edge_case_e0.001.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.001.gff
                URL_HASH SHA256=3c91be74c5473c098e507a6974755cba5f57f3266dc6c507e9c49fd92d9c11e5)
declare_datasource (FILE er_edge_case_e0.001.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.001.stdout
                URL_HASH SHA256=e7cc17d5d4fbfb5de38721e36ec795c6c226b9ed8e4030404dc659e31ce99c1e)
declare_datasource (FILE er_edge_case_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE er_edge_case_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.stdout
                URL_HASH SHA256=c847f28f5dba577a0912af93e5e9e6854c73333e3a0d653d1b84bcdc8abaab12)
