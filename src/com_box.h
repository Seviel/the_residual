/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_COM_BOX_H
#define SRC_COM_BOX_H

#include "core/include/sprite.h"
#include "core/include/text.h"

using namespace rinvid;

class ComBox final : public rinvid::Sprite
{

  public:
    /**************************************************************************************************
     * @brief Constructor.
     *
     *************************************************************************************************/
    ComBox();

    virtual void update(double delta_time) override;
    virtual void draw() override;

    void set_text(std::string text);

  private:
    Texture tex_;
    Text text_;
    std::string content_;
};

#endif // SRC_COM_BOX_H
