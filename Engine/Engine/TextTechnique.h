#ifndef TEXTTECHNIQUE_H
#define TEXTTECHNIQUE_H

// ----------------------------------------------------------------------------

#include "BaseTechnique.h"

// ----------------------------------------------------------------------------

class TextTechnique : public BaseTechnique
{
public:
	TextTechnique();
	virtual ~TextTechnique();

	virtual bool init() override;
	virtual void update() override;

	// ----------------------------------------------------------------------------

private:

	// ----------------------------------------------------------------------------
};

#endif // TEXTTECHNIQUE_H