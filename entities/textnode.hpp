#ifndef TEXTNODE_H
#define TEXTNODE_H

#include <string>

#include "scenenode.hpp"
#include "../Resources.hpp"

class TextNode : public SceneNode
{
public:
    TextNode(const std::string& text, const FontHolder& fonts);

    void            setText(const std::string& text);

private:
    virtual void    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Text        mText;
};

#endif // TEXTNODE_H
