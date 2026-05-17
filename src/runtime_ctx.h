/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_RUNTIME_CTX_H
#define SRC_RUNTIME_CTX_H

#include <rinvid/core/camera.h>
#include <rinvid/system/application.h>

#include "src/com_box.h"

using namespace rinvid;

class RuntimeCtx final
{
  public:
    RuntimeCtx()
    {
    }

    static ComBox* com_box();

    static Camera camera_;
    static ComBox* com_box_;
    static Application* app_;
};

#endif // SRC_RUNTIME_CTX_H
