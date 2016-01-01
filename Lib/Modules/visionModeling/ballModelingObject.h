#ifndef BALL_MODELING_OBJECT_H
#define BALL_MODELING_OBJECT_H

#include <stdint.h>
#include <filter/bootstrapfilter.h>
#include <model/systemmodel.h>
#include <model/measurementmodel.h>
#include "nonlinearSystemPdf.h"
#include "nonlinearMeasurementPdf.h"

class ballModelingObject
{
public:
	ballModelingObject();
	~ballModelingObject();
	//bool InitializeEnvironment();
	bool InitializeBootStrapFilter(MatrixWrapper::ColumnVector initState);
	bool RunOneStep(uint8_t *label, int width, int height, double headPitch);
	void clearBootstrap(void);

protected:
	bool refineObservation(); //this is the function to obtain the ball candidates;
	bool UpdateBallParameters(void);

protected:
	BFL::NonlinearSystemPdf *psys_pdf;
	BFL::SystemModel<MatrixWrapper::ColumnVector> *psys_model;
	BFL::NonlinearMeasurementPdf *pmeas_pdf;
	BFL::MeasurementModel<preprocessedObservation, MatrixWrapper::ColumnVector> *pmeas_model;
	BFL::MCPdf<MatrixWrapper::ColumnVector> *pprior_discr;
	BFL::BootstrapFilter<MatrixWrapper::ColumnVector, preprocessedObservation> *pfilter;
	preprocessedObservation *pobs;

};

#endif
