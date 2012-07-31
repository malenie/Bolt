

//#include "stdafx.h"  // not present in the bolt/cl dir, but don't really need it 
#include <bolt/cl/bolt.h>
#include <bolt/unicode.h>

#include <iostream>
#include <fstream>
#include <streambuf>
#include <direct.h>  //windows CWD for error message
#include <tchar.h>
#include <algorithm>

namespace bolt {
	namespace cl {

    std::string clErrorString( const cl_int& status )
    {
        switch( status )
        {
            case CL_INVALID_DEVICE_PARTITION_COUNT:
                return "CL_INVALID_DEVICE_PARTITION_COUNT";
            case CL_INVALID_LINKER_OPTIONS:
                return "CL_INVALID_LINKER_OPTIONS";
            case CL_INVALID_COMPILER_OPTIONS:
                return "CL_INVALID_COMPILER_OPTIONS";
            case CL_INVALID_IMAGE_DESCRIPTOR:
                return "CL_INVALID_IMAGE_DESCRIPTOR";
            case CL_INVALID_PROPERTY:
                return "CL_INVALID_PROPERTY";
            case CL_INVALID_GLOBAL_WORK_SIZE:
                return "CL_INVALID_GLOBAL_WORK_SIZE";
            case CL_INVALID_MIP_LEVEL:
                return "CL_INVALID_MIP_LEVEL";
            case CL_INVALID_BUFFER_SIZE:
                return "CL_INVALID_BUFFER_SIZE";
            case CL_INVALID_GL_OBJECT:
                return "CL_INVALID_GL_OBJECT";
            case CL_INVALID_OPERATION:
                return "CL_INVALID_OPERATION";
            case CL_INVALID_EVENT:
                return "CL_INVALID_EVENT";
            case CL_INVALID_EVENT_WAIT_LIST:
                return "CL_INVALID_EVENT_WAIT_LIST";
            case CL_INVALID_GLOBAL_OFFSET:
                return "CL_INVALID_GLOBAL_OFFSET";
            case CL_INVALID_WORK_ITEM_SIZE:
                return "CL_INVALID_WORK_ITEM_SIZE";
            case CL_INVALID_WORK_GROUP_SIZE:
                return "CL_INVALID_WORK_GROUP_SIZE";
            case CL_INVALID_WORK_DIMENSION:
                return "CL_INVALID_WORK_DIMENSION";
            case CL_INVALID_KERNEL_ARGS:
                return "CL_INVALID_KERNEL_ARGS";
            case CL_INVALID_ARG_SIZE:
                return "CL_INVALID_ARG_SIZE";
            case CL_INVALID_ARG_VALUE:
                return "CL_INVALID_ARG_VALUE";
            case CL_INVALID_ARG_INDEX:
                return "CL_INVALID_ARG_INDEX";
            case CL_INVALID_KERNEL:
                return "CL_INVALID_KERNEL";
            case CL_INVALID_KERNEL_DEFINITION:
                return "CL_INVALID_KERNEL_DEFINITION";
            case CL_INVALID_KERNEL_NAME:
                return "CL_INVALID_KERNEL_NAME";
            case CL_INVALID_PROGRAM_EXECUTABLE:
                return "CL_INVALID_PROGRAM_EXECUTABLE";
            case CL_INVALID_PROGRAM:
                return "CL_INVALID_PROGRAM";
            case CL_INVALID_BUILD_OPTIONS:
                return "CL_INVALID_BUILD_OPTIONS";
            case CL_INVALID_BINARY:
                return "CL_INVALID_BINARY";
            case CL_INVALID_SAMPLER:
                return "CL_INVALID_SAMPLER";
            case CL_INVALID_IMAGE_SIZE:
                return "CL_INVALID_IMAGE_SIZE";
            case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
                return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
            case CL_INVALID_MEM_OBJECT:
                return "CL_INVALID_MEM_OBJECT";
            case CL_INVALID_HOST_PTR:
                return "CL_INVALID_HOST_PTR";
            case CL_INVALID_COMMAND_QUEUE:
                return "CL_INVALID_COMMAND_QUEUE";
            case CL_INVALID_QUEUE_PROPERTIES:
                return "CL_INVALID_QUEUE_PROPERTIES";
            case CL_INVALID_CONTEXT:
                return "CL_INVALID_CONTEXT";
            case CL_INVALID_DEVICE:
                return "CL_INVALID_DEVICE";
            case CL_INVALID_PLATFORM:
                return "CL_INVALID_PLATFORM";
            case CL_INVALID_DEVICE_TYPE:
                return "CL_INVALID_DEVICE_TYPE";
            case CL_INVALID_VALUE:
                return "CL_INVALID_VALUE";
            case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
                return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";
            case CL_DEVICE_PARTITION_FAILED:
                return "CL_DEVICE_PARTITION_FAILED";
            case CL_LINK_PROGRAM_FAILURE:
                return "CL_LINK_PROGRAM_FAILURE";
            case CL_LINKER_NOT_AVAILABLE:
                return "CL_LINKER_NOT_AVAILABLE";
            case CL_COMPILE_PROGRAM_FAILURE:
                return "CL_COMPILE_PROGRAM_FAILURE";
            case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
                return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
            case CL_MISALIGNED_SUB_BUFFER_OFFSET:
                return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
            case CL_MAP_FAILURE:
                return "CL_MAP_FAILURE";
            case CL_BUILD_PROGRAM_FAILURE:
                return "CL_BUILD_PROGRAM_FAILURE";
            case CL_IMAGE_FORMAT_NOT_SUPPORTED:
                return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
            case CL_IMAGE_FORMAT_MISMATCH:
                return "CL_IMAGE_FORMAT_MISMATCH";
            case CL_MEM_COPY_OVERLAP:
                return "CL_MEM_COPY_OVERLAP";
            case CL_PROFILING_INFO_NOT_AVAILABLE:
                return "CL_PROFILING_INFO_NOT_AVAILABLE";
            case CL_OUT_OF_HOST_MEMORY:
                return "CL_OUT_OF_HOST_MEMORY";
            case CL_OUT_OF_RESOURCES:
                return "CL_OUT_OF_RESOURCES";
            case CL_MEM_OBJECT_ALLOCATION_FAILURE:
                return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
            case CL_COMPILER_NOT_AVAILABLE:
                return "CL_COMPILER_NOT_AVAILABLE";
            case CL_DEVICE_NOT_AVAILABLE:
                return "CL_DEVICE_NOT_AVAILABLE";
            case CL_DEVICE_NOT_FOUND:
                return "CL_DEVICE_NOT_FOUND";
            case CL_SUCCESS:
                return "CL_SUCCESS";
            default:
                return "Error code not defined";
            break;
        }
    }

	std::string fileToString(const std::string &fileName)
	{
		std::ifstream infile (fileName);
		if (infile.fail() ) {
#if defined( _WIN32 )
			TCHAR osPath[ MAX_PATH ];

			//	If loading the .cl file fails from the specified path, then make a last ditch attempt (purely for convenience) to find the .cl file right to the executable,
			//	regardless of what the CWD is
			//	::GetModuleFileName( ) returns TCHAR's (and we define _UNICODE for windows); but the fileName string is char's, 
			//	so we needed to create an abstraction for string/wstring
			if( ::GetModuleFileName( NULL, osPath, MAX_PATH ) )
			{
				bolt::tstring thisPath( osPath );
				bolt::tstring::size_type pos = thisPath.find_last_of( _T( "\\" ) );

				bolt::tstring newPath;
				if( pos != bolt::tstring::npos )
				{
					bolt::tstring exePath	= thisPath.substr( 0, pos + 1 );	// include the \ character

					//	Narrow to wide conversion should always work, but beware of wide to narrow!
					bolt::tstring convName( fileName.begin( ), fileName.end( ) );
					newPath = exePath + convName;
				}

				infile.open( newPath.c_str( ) );
			}
#endif
			if (infile.fail() ) {
				TCHAR cCurrentPath[FILENAME_MAX];
				if (_tgetcwd(cCurrentPath, sizeof(cCurrentPath) / sizeof(TCHAR))) {
					bolt::tout <<  _T( "CWD=" ) << cCurrentPath << std::endl;
				};
				std::cout << "error: failed to open file '" << fileName << std::endl;
				throw;
			} 
		}

		std::string str((std::istreambuf_iterator<char>(infile)),
			std::istreambuf_iterator<char>());
		return str;
	};



	::cl::Kernel compileFunctor(const std::string &kernelCodeString, const std::string kernelName,  std::string compileOptions, const control &c)
	{

		if (c.debug() & control::debug::ShowCode) {
			std::cout << "debug: code=" << std::endl << kernelCodeString;
		}

		::cl::Program mainProgram(c.context(), kernelCodeString, false);
		try
		{
			compileOptions += c.compileOptions();
			compileOptions += " -x clc++";

			if (c.compileForAllDevices()) {
				std::vector<::cl::Device> devices = c.context().getInfo<CL_CONTEXT_DEVICES>();

				mainProgram.build(devices, compileOptions.c_str());
			} else {
				std::vector<::cl::Device> devices;
				devices.push_back(c.device());
				mainProgram.build(devices, compileOptions.c_str());
			};




		} catch(::cl::Error e) {
			std::cout << "Code         :\n" << kernelCodeString << std::endl;

			std::vector<::cl::Device> devices = c.context().getInfo<CL_CONTEXT_DEVICES>();
			std::for_each(devices.begin(), devices.end(), [&] (::cl::Device &d) {
				if (mainProgram.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(d) != CL_SUCCESS) {
					std::cout << "Build status for device: " << d.getInfo<CL_DEVICE_NAME>() << "_"<< d.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << "CU_"<< d.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << "Mhz" << "\n";
					std::cout << "    Build Status: " << mainProgram.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(d) << std::endl;
					std::cout << "    Build Options:\t" << mainProgram.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(d) << std::endl;
					std::cout << "    Build Log:\t " << mainProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(d) << std::endl;
				}
			});
			throw e;
		}

		if ( c.debug() & control::debug::Compile) {
			std::vector<::cl::Device> devices = c.context().getInfo<CL_CONTEXT_DEVICES>();
			std::for_each(devices.begin(), devices.end(), [&] (::cl::Device &d) {
				std::cout << "debug: Build status for device: " << d.getInfo<CL_DEVICE_NAME>() << "_"<< d.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << "CU_"<< d.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>() << "Mhz" << "\n";
				std::cout << "debug:   Build Status: " << mainProgram.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(d) << std::endl;
				std::cout << "debug:   Build Options:\t" << mainProgram.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(d) << std::endl;
				std::cout << "debug:   Build Log:\n " << mainProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(d) << std::endl;
			}); 
		};

		return ::cl::Kernel(mainProgram, kernelName.c_str());
	}



	void constructAndCompile(::cl::Kernel *masterKernel, const std::string &apiName, const std::string instantiationString, std::string userCode, std::string valueTypeName,  std::string functorTypeName, const control &c) {

		//FIXME, when this becomes more stable move the kernel code to a string in bolt.cpp
		// Note unfortunate dependency here on relative file path of run directory and location of bolt::cl dir.
		std::string templateFunctionString = bolt::cl::fileToString( apiName + "_kernels.cl"); 

		std::string codeStr = userCode + "\n\n" + templateFunctionString +   instantiationString;


		std::string compileOptions = "";
		if (c.debug() & control::debug::SaveCompilerTemps) {
			compileOptions += "-save-temps=BOLT";
		}

		if (c.debug() & control::debug::Compile) {
			std::cout << "debug: compiling algorithm: '" << apiName << "' with valueType='" << valueTypeName << "'" << " ;  functorType='" << functorTypeName << "'" << std::endl;
		}




		*masterKernel = bolt::cl::compileFunctor(codeStr, apiName + "Instantiated", compileOptions, c);
	};





	};
};
