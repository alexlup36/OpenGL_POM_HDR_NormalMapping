#ifndef SIMPLECOLORTECHNIQUE_H
#define SIMPLECOLORTECHNIQUE_H

// ----------------------------------------------------------------------------

#include "LightUtil.h"
#include "TransformTechnique.h"

#include <vector>

// ----------------------------------------------------------------------------

class SimpleColorTechnique : public TransformTechnique
{
public:
	SimpleColorTechnique();
	virtual ~SimpleColorTechnique();

	// ------------------------------------------------------------------------

	virtual bool init() override;
	virtual void update() override;

private:

	// ------------------------------------------------------------------------
};


#endif // SIMPLECOLORTECHNIQUE_H