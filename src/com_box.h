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

#include <string>

#include <rinvid/core/sprite.h>
#include <rinvid/core/text.h>

#include "src/text_role.h"

using namespace rinvid;

class ComBox final : public rinvid::Sprite
{

  public:
    /**************************************************************************************************
     * @brief Constructor.
     *
     *************************************************************************************************/
    explicit ComBox(rinvid::Texture& texture);

    virtual void update(double delta_time);
    virtual void draw() override;

    void set_text(std::string text, TextRole role = TextRole::Player);

  private:
    Text text_;
    std::string source_text_;
    std::string content_;
    TextRole role_{TextRole::Player};
};

#endif // SRC_COM_BOX_H
