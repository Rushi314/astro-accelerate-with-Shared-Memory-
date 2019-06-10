#ifndef ASTRO_ACCELERATE_AA_PIPELINE_HPP
#define ASTRO_ACCELERATE_AA_PIPELINE_HPP

#include <set>
#include <string>

/**
 * \namespace astroaccelerate
 * \brief A project-wide namespace astroaccelerate is used to separate the implementation of the library from library users.
 */
namespace astroaccelerate {
  
  /**
   * \namespace astroaccelerate::aa_pipeline
   * \brief The namespace that contains component names and the concept of a pipeline consisting of components.
   */
  namespace aa_pipeline {

    /** \enum debug
     * \brief Contains debug flags.
     */
    enum class debug : int {
		debug = 0,
		analysis
	};
    
    /** \enum component
     * \brief Contains the selectable components.
     */
    enum class component : int {
		empty = 0,
		dedispersion,
		analysis,
		periodicity,
		fdas,
    };
    
    /** \enum component_option
     * \brief Contains options for components.
     */
    enum class component_option : int {
		empty = 0, //< The trivial component.
		zero_dm,                //< DDTR - performs zero DM normalization
		zero_dm_with_outliers,  //< DDTR - performs zero DM normalization with outliers rejection
		old_rfi,                //< DDTR - performs rfi mitigation
		copy_ddtr_data_to_host, //< DDTR - switch to copy ddtr data to host
		output_dmt,             //< DDTR - Switches on output of ddtr to disk.
		msd_baseline_noise,     //< MSD
		candidate_algorithm,    //< CND - Enables/disables the candidate_algorithm
		output_ffdot_plan,      //< FDAS - Switches on output of ffdot_plan to disk.
		output_fdas_list,       //< FDAS - Switches on output of fdas_list to disk.
		fdas_custom_fft,        //< FDAS - Switches on output of custom_fft.
		fdas_inbin,             //< FDAS - Switches on inbin for fdas.
		fdas_norm               //< FDAS - Switches on norm for fdas.
    };
    
    /** \brief Function to convert component types into strings so that the user can query the pipeline. */
    inline const std::string component_name(const aa_pipeline::component &component) {
		switch (component) {
			case aa_pipeline::component::empty:
				return "empty";
				break;
			case aa_pipeline::component::dedispersion:
				return "dedispersion";
				break;
			case aa_pipeline::component::analysis:
				return "analysis";
				break;
			case aa_pipeline::component::fdas:
				return "fdas";
				break;
			case aa_pipeline::component::periodicity:
				return "periodicity";
				break;
			default:
				return "ERROR: Component name not found";
				break;
		}
    }
	
    /** \brief Function to convert component types into strings so that the user can query the pipeline. */
    inline const std::string component_option_name(const aa_pipeline::component_option &component) {
		switch (component) {
			case aa_pipeline::component_option::empty:
				return "empty";
				break;
			case aa_pipeline::component_option::zero_dm:
				return "DDTR will perform zero DM";
				break;
			case aa_pipeline::component_option::zero_dm_with_outliers:
				return "DDTR will perform zero DM with outlier rejection";
				break;	
			case aa_pipeline::component_option::old_rfi:
				return "DDTR will perform old rfi mitigation";
				break;
			case aa_pipeline::component_option::copy_ddtr_data_to_host:
				return "DDTR will copy de-dispersed data to host";
				break;
			case aa_pipeline::component_option::output_dmt:
				return "DDTR will output de-dispersed data to disc";
				break;
			case aa_pipeline::component_option::msd_baseline_noise:
				return "MSD will perform outlier rejection";
				break;
			case aa_pipeline::component_option::candidate_algorithm:
				return "Candidate algorithm is threshold only";
				break;
			case aa_pipeline::component_option::output_ffdot_plan:
				return "FDAS will write f-f_dot planes to disk (need a lot of space!)";
				break;
			case aa_pipeline::component_option::output_fdas_list:
				return "FDAS will write candidates to disk";
				break;
			case aa_pipeline::component_option::fdas_custom_fft:
				return "FDAS will use custom FFT convolution algorithm";
				break;
			case aa_pipeline::component_option::fdas_inbin:
				return "FDAS will use interbinning";
				break;
			case aa_pipeline::component_option::fdas_norm:
				return "FDAS will perform spectrum whitening (red noise normalization)";
				break;
			
			default:
				return "ERROR: Component name not found";
				break;
		}
    }
    
    typedef std::set<aa_pipeline::component> pipeline; /**< A pipeline is a collection of components. */
    typedef std::set<aa_pipeline::component_option> pipeline_option; /**< All pipeline options contained in pipeline_option. */
    
  } // namespace aa_pipeline
} // namespace astroaccelerate


#endif // ASTRO_ACCELERATE_AA_PIPELINE_HPP
