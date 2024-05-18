// Include libraries and functions

/*
LAT_OFF, LONG_OFF e HEIGHT_OFF são valores de compensação, 
LAT_SCALE, LONG_SCALE e HEIGHT_SCALE são valores de escala
Esses valores são próprios para cada imagem e estão presentes 
nos arquivos de metadados da imagem
*/

// functions

/*
function to take the a general value related to each 
point (lat, long, height, line, collumn, for example) and normalize them
*/

void GeodeticNormalization(long value, long CorrectionFactor, long ScaleFactor){
    long normalizedValue  = (value - CorrectionFactor)/ScaleFactor;
}

/* Function to normalize the values in parallel */
void ParallelNorm(){};
