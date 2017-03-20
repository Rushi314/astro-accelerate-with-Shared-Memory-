#include "../DedispersionStrategy.h"

namespace astroaccelerate{

	DedispersionStrategy::DedispersionStrategy()
	{
		_multi_file = 1;
		_enable_debug = 0;
		_enable_analysis = 0;
		_enable_periodicity = 0;
		_enable_acceleration = 0;
		_enable_fdas_custom_fft = 1;
		_enable_fdas_inbin = 0;
		_enable_fdas_norm = 0;
		_output_dmt = 0;
		_enable_zero_dm = 0;
		_enable_zero_dm_with_outliers = 0;
		_enable_rfi = 0;
		_nboots = -1;
		_ntrial_bins = 0;
		_navdms	= 1;
		_narrow = 0.001f;
		_aggression = 2.5;
		_nsearch = 3;
		_power = 2.0f;
		_sigma_cutoff = 6.0f;
		_sigma_constant = 0.4f;
		_max_boxcar_width_in_sec = 0.5f;
		_wide = 0.1f;
		_range = 0;
		_user_dm_low = nullptr;
		_user_dm_high = nullptr;
		_user_dm_step = nullptr;
		_in_bin = nullptr;
		_out_bin = nullptr;
		_maxshift = 0;
		_dm_low = nullptr;
		_dm_high = nullptr;
		_dm_step = nullptr;
		_dmshifts = nullptr;
		_ndms = nullptr;
		_max_ndms = 0;
		_total_ndms	= 0;
		_max_dm	= 0.0f;
		_t_processed = nullptr;
		_nbits = 0;
		_nifs = 0;
		_tstart = 0.0f;
		_tsamp = 0.0f;
		_nsamp = 0;
		_nsamples = 0;
		_max_samps = 0;
		_nchans = 0;
		_fch1 = 0.0f;
		_foff = 0.0f;
		_num_tchunks = 0;
	}

	DedispersionStrategy::~DedispersionStrategy()
	{
		// free all the pointers
		free(_dm_low);
		free(_dm_high);
		free(_dm_step);
		free(_dmshifts);
		free(_ndms);
		for(int i = 0; i < _range; ++i)
			free(_t_processed[i]);
		free(_t_processed);
	}
	// Setters

	// Getters
	int DedispersionStrategy::get_multi_file() const { return _multi_file;}
	int DedispersionStrategy::get_enable_debug() const { return _enable_debug;}
	int DedispersionStrategy::get_enable_analysis() const { return _enable_analysis;}
	int DedispersionStrategy::get_enable_periodicity() const { return _enable_periodicity;}
	int DedispersionStrategy::get_enable_acceleration() const { return _enable_acceleration;}
	int DedispersionStrategy::get_output_dmt() const { return _output_dmt;}
	int DedispersionStrategy::get_enable_zero_dm() const { return _enable_zero_dm;}
	int DedispersionStrategy::get_enable_zero_dm_with_outliers() const { return _enable_zero_dm_with_outliers;}
	int DedispersionStrategy::get_enable_rfi() const { return _enable_rfi;}
	int DedispersionStrategy::get_enable_fdas_custom_fft() const { return _enable_fdas_custom_fft;}
	int DedispersionStrategy::get_enable_fdas_inbin() const { return _enable_fdas_inbin;}
	int DedispersionStrategy::get_enable_fdas_norm() const { return _enable_fdas_norm;}
	int DedispersionStrategy::get_nboots() const { return _nboots;}
	int DedispersionStrategy::get_ntrial_bins() const { return _ntrial_bins;}
	int DedispersionStrategy::get_navdms() const { return _navdms;}
	float DedispersionStrategy::get_narrow() const { return _narrow;}
	float DedispersionStrategy::get_aggression() const { return _aggression;}
	int DedispersionStrategy::get_nsearch() const { return _nsearch;}
	float DedispersionStrategy::get_power() const { return _power;}
	float DedispersionStrategy::get_sigma_cutoff() const { return _sigma_cutoff;}
	float DedispersionStrategy::get_sigma_constant() const { return _sigma_constant;}
	float DedispersionStrategy::get_max_boxcar_width_in_sec() const { return _max_boxcar_width_in_sec;}
	float DedispersionStrategy::get_wide() const { return _wide;}
	int DedispersionStrategy::get_range() const { return _range;}
	float* DedispersionStrategy::get_user_dm_low() const { return _user_dm_low;}
	float* DedispersionStrategy::get_user_dm_high() const { return _user_dm_high;}
	float* DedispersionStrategy::get_user_dm_step() const { return _user_dm_step;}
	int* DedispersionStrategy::get_in_bin() const { return _in_bin;}
	int* DedispersionStrategy::get_out_bin() const { return _out_bin;}
	//
	int DedispersionStrategy::get_maxshift() const { return _maxshift;}
	float* DedispersionStrategy::get_dm_low() const {  return _dm_low;}
	float* DedispersionStrategy::get_dm_high() const { return _dm_high;}
	float* DedispersionStrategy::get_dm_step() const { return _dm_step;}
	float* DedispersionStrategy::get_dmshifts() const { return _dmshifts;}
	int* DedispersionStrategy::get_ndms() const { return _ndms;}
	int DedispersionStrategy::get_max_ndms() const { return _max_ndms;}
	int DedispersionStrategy::get_total_ndms() const { return _total_ndms;}
	float DedispersionStrategy::get_max_dm() const { return _max_dm;}
	int** DedispersionStrategy::get_t_processed() const { return _t_processed;}
	int DedispersionStrategy::get_nbits() const { return _nbits;}
	int DedispersionStrategy::get_nifs() const { return _nifs;}
	float DedispersionStrategy::get_tstart() const { return _tstart;}
	float DedispersionStrategy::get_tsamp() const { return _tsamp;}
	int DedispersionStrategy::get_nsamp() const { return _nsamp;}
	int DedispersionStrategy::get_nsamples() const { return _nsamples;}
	int DedispersionStrategy::get_max_samps() const { return _max_samps;}
	int DedispersionStrategy::get_nchans() const { return _nchans;}
	float DedispersionStrategy::get_fch1() const { return _fch1;}
	float DedispersionStrategy::get_foff() const { return _foff;}
	unsigned int DedispersionStrategy::get_num_tchunks() const { return _num_tchunks;}

	void DedispersionStrategy::make_strategy(size_t const gpu_memory)
	{
		// This method relies on defining points when nsamps is a multiple of
		// nchans - bin on the diagonal or a fraction of it.

		int i, j, c;
		int maxshift_high = 0;

		float n;
		float fmin = ( _fch1 + ( _foff * _nchans ) );
		float fmin_pow = powf(fmin, _power);
		float fmax_pow = powf(_fch1, _power);

		_dm_low = (float *) malloc(( _range ) * sizeof(float));
		_dm_high = (float *) malloc(( _range ) * sizeof(float));
		_dm_step = (float *) malloc(( _range ) * sizeof(float));
		_ndms = (int *) malloc(( _range ) * sizeof(int));

		_dmshifts = (float *) malloc(_nchans * sizeof(float));

		//{{{ Calculate maxshift, the number of dms for this bin and
		//the highest value of dm to be calculated in this bin

		if (_power != 2.0) {
			// Calculate time independent dm shifts
			for (c = 0; c < _nchans; c++)
			{
				( _dmshifts )[c] = 4148.741601f * ( ( 1.0 / pow(( _fch1 + ( _foff * c ) ), _power) ) - ( 1.0 / pow(_fch1, _power) ) );
			}
		}
		else {
			// Calculate time independent dm shifts
			for (c = 0; c < _nchans; c++)
			{
				_dmshifts[c] = (float) ( 4148.741601f * ( ( 1.0 / pow((double) ( _fch1 + ( _foff * c ) ), _power) ) - ( 1.0 / pow((double) _fch1, _power) ) ) );
			}
		}

		for (i = 0; i < _range; i++)	{
			modff(( ( (int) ( ( _user_dm_high[i] - _user_dm_low[i] ) / _user_dm_step[i] ) + SDIVINDM ) / SDIVINDM ), &n);
			_ndms[i] = (int) ( (int) n * SDIVINDM );
			if (_max_ndms < _ndms[i])
				_max_ndms = _ndms[i];
			_total_ndms = _total_ndms + _ndms[i];
		}
		printf("\nMaximum number of dm trials in any of the range steps:\t%d", _max_ndms);

		_dm_low[0] = _user_dm_low[0];
		_dm_high[0] = _ndms[0] * _user_dm_step[0];
		_dm_step[0] = _user_dm_step[0];
		for (i = 1; i < _range; i++)	{
			_dm_low[i] = _dm_high[i - 1];
			_dm_high[i] = _dm_low[i] + _ndms[i] * _user_dm_step[i];
			_dm_step[i] = _user_dm_step[i];

			if (_in_bin[i - 1] > 1) {
				_maxshift = (int) ceil(( ( _dm_low[i - 1] + _dm_step[i - 1] * _ndms[i - 1] ) * _dmshifts[_nchans - 1] ) / _tsamp);
				_maxshift = (int) ceil((float) ( _maxshift + ( (float) ( SDIVINT * ( SNUMREG ) ) ) ) / (float) _in_bin[i - 1]) / (float) ( SDIVINT * ( SNUMREG ) );
				_maxshift = _maxshift * ( SDIVINT * ( SNUMREG ) ) * _in_bin[i - 1];
				if (_maxshift > maxshift_high)
					maxshift_high = _maxshift;
			}
		}

		if (_in_bin[_range - 1] > 1) {
			_maxshift = (int) ceil(( ( _dm_low[_range - 1] + _dm_step[_range - 1] * _ndms[_range - 1] ) * _dmshifts[_nchans - 1] ) / _tsamp);
			_maxshift = (int) ceil((float) ( _maxshift + ( (float) ( SDIVINT * ( SNUMREG ) ) ) ) / (float) _in_bin[_range - 1]) / (float) ( SDIVINT * ( SNUMREG ) );
			_maxshift = _maxshift * ( SDIVINT * ( SNUMREG ) ) * _in_bin[_range - 1];
			if (_maxshift > maxshift_high)
				maxshift_high = _maxshift;
		}

		if (maxshift_high == 0)	{
			maxshift_high = (int) ceil(( ( _dm_low[_range - 1] + _dm_step[_range - 1] * ( _ndms[_range - 1] ) ) * _dmshifts[_nchans - 1] ) / _tsamp);
		}
		_max_dm = ceil(_dm_high[_range - 1]);

		_maxshift = ( maxshift_high + 2 * ( SNUMREG * SDIVINT ) );
		printf("\nRange:\t%d, MAXSHIFT:\t%d, Scrunch value:\t%d", _range - 1, _maxshift, _in_bin[_range - 1]);
		printf("\nMaximum dispersive delay:\t%.2f (s)", _maxshift * _tsamp);

		if (_maxshift >= _nsamp)	{
			printf("\n\nERROR!! Your maximum DM trial exceeds the number of samples you have.\nReduce your maximum DM trial\n\n");
			exit(1);
		}

		printf("\nDiagonal DM:\t%f", ( _tsamp * _nchans * 0.0001205 * powf(( _fch1 + ( _foff * ( _nchans / 2 ) ) ), 3.0) ) / ( -_foff * _nchans ));
		if (_maxshift >= _nsamp)	{
			printf("ERROR!! Your maximum DM trial exceeds the number of samples you have.\nReduce your maximum DM trial");
			exit(1);
		}

		/* Four cases:
		 * 1) nchans < max_ndms & nsamp fits in GPU RAM
		 * 2) nchans > max_ndms & nsamp fits in GPU RAM
		 * 3) nchans < max_ndms & nsamp does not fit in GPU RAM
		 * 4) nchans > max_ndms & nsamp does not fit in GPU RAM
		 */

		int max_tsamps;

		// Allocate memory to store the t_processed ranges:
		_t_processed = (int **) malloc(_range * sizeof(int *));

		if (_nchans < _max_ndms ) {
			// This means that we can cornerturn into the allocated output buffer
			// without increasing the memory needed

			// Maximum number of samples we can fit in our GPU RAM is then given by:
			max_tsamps = (int) ( ( gpu_memory ) / ( sizeof(unsigned short) * ( _max_ndms  + _nchans ) ) );

			// Check that we dont have an out of range maxshift:
			if (_maxshift  > max_tsamps)	{
				printf("\nERROR!! Your GPU doesn't have enough memory for this number of dispersion trials.");
				printf("\nReduce your maximum dm or increase the size of your dm step");
				exit(0);
			}

			// Next check to see if nsamp fits in GPU RAM:
			if (_nsamp < max_tsamps)	{
				// We have case 1)
				// Allocate memory to hold the values of nsamps to be processed
				int local_t_processed = (int) floor(( (float) ( _nsamp - _maxshift ) / (float) _in_bin[_range - 1] ) / (float) ( SDIVINT * ( SNUMREG ) ));
				local_t_processed = local_t_processed * ( SDIVINT * ( SNUMREG ) ) * _in_bin[_range - 1];
				for (i = 0; i < _range; i++)	{
					_t_processed[i] = (int *) malloc(sizeof(int));
					_t_processed[i][0] = (int) floor(( (float) ( local_t_processed ) / (float) _in_bin[i] ) / (float) ( SDIVINT * ( SNUMREG ) ));
					_t_processed[i][0] = _t_processed[i][0] * ( SDIVINT * ( SNUMREG ) );
				}
				_num_tchunks = 1;
				printf("\nIn 1\n");
			}
			else {
				// We have case 3)
				// Work out how many time samples we can fit into ram
				int samp_block_size = max_tsamps - _maxshift;
				//int samp_block_size = max_tsamps;

				// Work out how many blocks of time samples we need to complete the processing
				// upto nsamp-maxshift
				//int num_blocks = (int) floor(( (float) nsamp - ( *maxshift ) )) / ( (float) ( samp_block_size ) ) + 1;

				// Find the common integer amount of samples between all bins
				int local_t_processed = (int) floor(( (float) ( samp_block_size ) / (float) _in_bin[_range - 1] ) / (float) ( SDIVINT * ( SNUMREG ) ));
				local_t_processed = local_t_processed * ( SDIVINT * ( SNUMREG ) ) * _in_bin[_range - 1];

				int num_blocks = (int) floor(( (float) _nsamp - _maxshift )) / ( (float) ( local_t_processed ) ) + 1;

				// Work out the remaining fraction to be processed
				int remainder = ( _nsamp - ( ( num_blocks - 1 ) * local_t_processed ) - _maxshift );
				remainder = (int) floor((float) remainder / (float) _in_bin[_range - 1]) / (float) ( SDIVINT * ( SNUMREG ) );
				remainder = remainder * ( SDIVINT * ( SNUMREG ) ) * _in_bin[_range - 1];

				for (i = 0; i < _range; i++)	{
					// Allocate memory to hold the values of nsamps to be processed
					_t_processed[i] = (int *) malloc(num_blocks * sizeof(int));
					// Remember the last block holds less!
					for (j = 0; j < num_blocks - 1; j++) {
						_t_processed[i][j] = (int) floor(( (float) ( local_t_processed ) / (float) _in_bin[i] ) / (float) ( SDIVINT * ( SNUMREG ) ));
						_t_processed[i][j] = _t_processed[i][j] * ( SDIVINT * ( SNUMREG ) );
					}
					// fractional bit
					_t_processed[i][num_blocks - 1] = (int) floor(( (float) ( remainder ) / (float) _in_bin[i] ) / (float) ( SDIVINT * ( SNUMREG ) ));
					_t_processed[i][num_blocks - 1] = _t_processed[i][num_blocks - 1] * ( SDIVINT * ( SNUMREG ) );
				}
				_num_tchunks = num_blocks;
				printf("\nIn 3\n");
				printf("\nnum_blocks:\t%d", num_blocks);
			}
		}
		else {
			// This means that we cannot cornerturn into the allocated output buffer
			// without increasing the memory needed. Set the output buffer to be as large as the input buffer:

			// Maximum number of samples we can fit in our GPU RAM is then given by:
			max_tsamps = (int) ( ( gpu_memory ) / ( _nchans * ( sizeof(float) + 2 * sizeof(unsigned short) ) ) );

			// Check that we dont have an out of range maxshift:
			if (_maxshift > max_tsamps) {
				printf("\nERROR!! Your GPU doens't have enough memory for this number of dispersion trials.");
				printf("\nReduce your maximum dm or increase the size of your dm step");
				exit(0);
			}

			// Next check to see if nsamp fits in GPU RAM:
			if (_nsamp < max_tsamps) {
				// We have case 2)
				// Allocate memory to hold the values of nsamps to be processed
				int local_t_processed = (int) floor(( (float) ( _nsamp - _maxshift ) / (float) _in_bin[_range - 1] ) / (float) ( SDIVINT * ( SNUMREG ) ));
				local_t_processed = local_t_processed * ( SDIVINT * ( SNUMREG ) ) * _in_bin[_range - 1];
				for (i = 0; i < _range; i++) {
					_t_processed[i] = (int *) malloc(sizeof(int));
					_t_processed[i][0] = (int) floor(( (float) ( local_t_processed ) / (float) _in_bin[i] ) / (float) ( SDIVINT * ( SNUMREG ) ));
					_t_processed[i][0] = _t_processed[i][0] * ( SDIVINT * ( SNUMREG ) );
				}
				_num_tchunks = 1;
				printf("\nIn 2\n");
			}
			else {
				// We have case 4)
				// Work out how many time samples we can fit into ram
				int samp_block_size = max_tsamps - _maxshift;

				// Work out how many blocks of time samples we need to complete the processing
				// upto nsamp-maxshift
				//int num_blocks = (int) floor(( (float) nsamp - (float) ( *maxshift ) ) / ( (float) samp_block_size ));

				// Find the common integer amount of samples between all bins
				int local_t_processed = (int) floor(( (float) ( samp_block_size ) / (float) _in_bin[_range - 1] ) / (float) ( SDIVINT * ( SNUMREG ) ));
				local_t_processed = local_t_processed * ( SDIVINT * ( SNUMREG ) ) * _in_bin[_range - 1];

				// samp_block_size was not used to calculate remainder instead there is local_t_processed which might be different
				int num_blocks = (int) floor(( (float) _nsamp - (float) _maxshift ) / ( (float) local_t_processed ));

				// Work out the remaining fraction to be processed
				int remainder = _nsamp - ( num_blocks * local_t_processed ) - _maxshift;

				for (i = 0; i < _range; i++)	{
					// Allocate memory to hold the values of nsamps to be processed
					_t_processed[i] = (int *) malloc(( num_blocks + 1 ) * sizeof(int));
					// Remember the last block holds less!
					for (j = 0; j < num_blocks; j++) {
						_t_processed[i][j] = (int) floor(( (float) ( local_t_processed ) / (float) _in_bin[i] ) / (float) ( SDIVINT * ( SNUMREG ) ));
						_t_processed[i][j] = _t_processed[i][j] * ( SDIVINT * ( SNUMREG ) );
					}
					// fractional bit
					_t_processed[i][num_blocks] = (int) floor(( (float) ( remainder ) / (float) _in_bin[i] ) / (float) ( SDIVINT * ( SNUMREG ) ));
					_t_processed[i][num_blocks] = _t_processed[i][num_blocks] * ( SDIVINT * ( SNUMREG ) );
				}
				_num_tchunks = num_blocks + 1;
				printf("\nIn 4\n");
			}
		}
		printf("\nMaxshift memory needed:\t%lu MB", _nchans * _maxshift * sizeof(unsigned short) / 1024 / 1024);
		if (_nchans < _max_ndms)	{
			printf("\nOutput memory needed:\t%lu MB", _max_ndms * _maxshift * sizeof(float) / 1024 / 1024);
		}
		else {
			printf("\nOutput memory needed:\t%lu MB", _nchans * _maxshift * sizeof(float) / 1024 / 1024);
		}
	}


} // namespace astroaccelerate
