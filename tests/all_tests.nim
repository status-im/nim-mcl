# mcl
# Copyright (c) 2025 Status Research & Development GmbH
# Licensed under either of
#  * Apache License, version 2.0, ([LICENSE-APACHE](LICENSE-APACHE))
#  * MIT license ([LICENSE-MIT](LICENSE-MIT))
# at your option.
# This file may not be copied, modified, or distributed except according to
# those terms

{.push raises: [].}

import
  ../mcl/bn

doAssert(mclBn_init(MCL_BN_SNARK1, MCLBN_COMPILED_TIME_VAR) == 0.cint, "FAILED TO EXECUTE mclBn_Init")
