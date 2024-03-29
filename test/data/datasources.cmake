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
                URL_HASH SHA256=42f618676a4906218c5acf38d0a72fe74e9b6ad6153b5c48914c966fa3873547)
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
                URL_HASH SHA256=008a409ed060f208a1931ff601a76174f7d6adb1c271f12d59b66369818dab07)
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
                URL_HASH SHA256=ff1e463b601a80acf0eb8c412efd50fa37b8ef479bec8ce92eaf39425ea55420)
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
                URL_HASH SHA256=9cefc9c829be946e83a363e49a69cac30f31fd4472fe968cf726478d157ebd48)
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
                URL_HASH SHA256=a40e1903ae98bc48f821c8c262e34992d5a1e6eb05b2e093b5be5b15edce424e)
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
                URL_HASH SHA256=e91270d33571278601d4dbc5f688834e83a17214fe54d809837cdead0d30b92a)
declare_datasource (FILE segment_0_500_800_e0.05.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_500_800_e0.05.gff
                URL_HASH SHA256=5a1319cd3704e9ea6da0f37711a95647d44db09cb69431a3ed508bde145fb8ad)
declare_datasource (FILE segment_0_500_800_e0.05.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_500_800_e0.05.stdout
                URL_HASH SHA256=d7ba016b3b02b09377b6a6a37d9d2e01d10f5ab97a35bbd6c82b7f03775fb8e6)
declare_datasource (FILE segment_0_500_800_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_500_800_e0.gff
                URL_HASH SHA256=33361a21310ee461e507d65642dd33f3ac1e7dbd064bc1890efddb468bb6bb9d)
declare_datasource (FILE segment_0_500_800_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/segment/0_500_800_e0.stdout
                URL_HASH SHA256=82215467a2a7514eb35707edef3ce71f09de0013e82c61e068c8ec2e3dd70600)
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
                URL_HASH SHA256=2387e314f3acc9130a170bb4e7284f6dac30c626d3cd213965ecd5afe9a4fde2)
declare_datasource (FILE er_edge_case_e0.0009.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.0009.gff
                URL_HASH SHA256=ce7648a8aa6496624c491ee899ce1ff8e00abe244383352d1e8425c36c4592fb)
declare_datasource (FILE er_edge_case_e0.0009.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.0009.stdout
                URL_HASH SHA256=5a79eb40971d32c93a7c71a90a9ce7bed24992b261b61f38112d15490a5d6b3d)
declare_datasource (FILE er_edge_case_e0.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE er_edge_case_e0.stdout
                URL ${CMAKE_SOURCE_DIR}/test/data/er_edge_case/e0.stdout
                URL_HASH SHA256=0aafe84b50d3beaa9768115a3a5fb99ca32dd18bcbb2aae17555ff5a0962cfe8)
