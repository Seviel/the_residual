/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "runtime_ctx.h"

Camera RuntimeCtx::camera_{};
ComBox* RuntimeCtx::com_box_{nullptr};

ComBox* RuntimeCtx::com_box()
{
    if (com_box_ == nullptr)
    {
        com_box_ = new ComBox();
    }

    return com_box_;
}
