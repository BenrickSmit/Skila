#! /bin/bash
##------------------------------------------------------------------------------------------
## SECTION: Base Variable Declarations
##------------------------------------------------------------------------------------------
HAS_DOXY="False"
PACKAGES=doxygen
GREEN=`tput setaf 10`
RED=`tput setaf 1`
BLUE=`tput setaf 33`
YELLOW=`tput setaf 11`
NC=`tput sgr0`
PRINT_RESULT="DONE"
DOCS_DIR=docs
DOCS_CONFIG_FILE=docs/cxx_config_file
WARN_DOC=docs/warning_logs.log
DOCS_SUCCESSFUL="True"
##------------------------------------------------------------------------------------------
## SECTION: Function Declarations
##------------------------------------------------------------------------------------------
print_color() {
	if [ "$2" == "RED" ]; then
		printf "${RED}${1}${NC}\n"
	elif [ "$2" == "YELLOW" ]; then
		printf "${YELLOW}${1}${NC}\n"
	elif [ "$2" == "BLUE" ]; then
		printf "${BLUE}${1}${NC}\n"
	elif [ "$2" == "GREEN" ]; then
		printf "${GREEN}${1}${NC}\n"
	else
		printf "$1\n"
	fi
}

# Used to determine whether a command is installed on the system
have_prog() {
    [ -x "$(which $1)" ]
}

verify_doxygen_installation() {
	# Determine whether doxygen is already intalled
	if have_prog doxygen ; then
		HAS_DOXY="True"
		PRINT_RESULT="DONE"
	else
		HAS_DOXY="False"
		PRINT_RESULT="ERROR"
	fi
}

# Used to install doxygen if it isn't installed already
install_doxygen() {
	# Echo the function's function
	print_color ""
	print_color ">>>> Validating doxygen Install..." "BLUE"

	# Determine whether doxygen is already intalled
	verify_doxygen_installation
	if [ ${HAS_DOXY} == "True" ] ; then
		print_color ">>>> \"${PACKAGES}\" ALREADY INSTALLED; Skipping..." "BLUE"
		return
	else
		print_color ">>>> \"${PACKAGES}\" NOT installed; Installing..." "BLUE"
	fi
	
	# Install Doxygen if it's not already installed
	if [ ${HAS_DOXY} == "False" ] ; then
		# Determine which installed to use
		if have_prog dnf ; then 
			sudo dnf install ${PACKAGES}
		elif have_prog apt-get ; then
			sudo apt-get install ${PACKAGES}
		elif have_prog pacman ; then
			sudo pacman -Syu install ${PACKAGES}
		elif have_prog apt ; then 
			sudo apt install ${PACKAGES}
		else
			print_color ">>>> NO PACKAGE MANAGER FOUND!" "RED"
			exit 2
		fi
	fi
	
	# Verify whether the programs have been installed successfully
	verify_doxygen_installation
	if [ ${HAS_DOXY} == "True" ] ; then
		printf "${BLUE}>>>> Installation of \"${PACKAGES}\" ? ${NC}"
		print_color "[ ${PRINT_RESULT} ]" "GREEN" 
	else 
		printf "${BLUE}>>>> Installation of \"${PACKAGES}\" ? ${NC}"
		print_color "[ ${PRINT_RESULT} ]" "RED"
		exit 2
	fi
}

configure_doxygen() {
	# Echo the function's function
	print_color ""
	print_color ">>>> Configuring doxygen with Project Information..." "BLUE"

	# Create the docs directory
	if [ -d ${DOCS_DIR} ] ; then
		rm -rf ${DOCS_DIR}
	fi
	mkdir ${DOCS_DIR}
	
	# Create the warning file
	if [ -d ${WARN_DOC} ] ; then
		rm -rf ${WARN_DOC}
	fi
	touch ${WARN_DOC}

	# Setup the doxygen configuration file
	doxygen -g ${DOCS_CONFIG_FILE}
	
	# Update the config file to the predefined settings
	PROJECT_NAME="$( cat build_info/build_name.txt )"
	PROJECT_VERSION="$( cat build_info/build_version.txt )"
	sed -i "s/PROJECT_NAME           = \"My Project\"/PROJECT_NAME           = \""${PROJECT_NAME}"\"/" ${DOCS_CONFIG_FILE}
	sed -i "s/OUTPUT_DIRECTORY       =/OUTPUT_DIRECTORY       = "${DOCS_DIR}"/" ${DOCS_CONFIG_FILE}
	sed -i "s/PROJECT_NUMBER         =/PROJECT_NUMBER         = "${PROJECT_VERSION}"/" ${DOCS_CONFIG_FILE}
	sed -i "s/QT_AUTOBRIEF           = NO/QT_AUTOBRIEF           = YES/" ${DOCS_CONFIG_FILE}
	sed -i "s/BUILTIN_STL_SUPPORT    = NO/BUILTIN_STL_SUPPORT    = YES/" ${DOCS_CONFIG_FILE}
	sed -i "s/NUM_PROC_THREADS       = 1/NUM_PROC_THREADS       = 0/" ${DOCS_CONFIG_FILE}
	sed -i "s/QUIET                  = NO/QUIET                  = YES/" ${DOCS_CONFIG_FILE}
	sed -i "s|WARN_LOGFILE           =|WARN_LOGFILE           = "${WARN_DOC}"|" ${DOCS_CONFIG_FILE}
	sed -i "s/HTML_TIMESTAMP         = NO/HTML_TIMESTAMP         = YES/" ${DOCS_CONFIG_FILE}
	sed -i "s/GENERATE_XML           = NO/GENERATE_XML           = YES/" ${DOCS_CONFIG_FILE}
	sed -i "s/GENERATE_DOCBOOK       = NO/GENERATE_DOCBOOK       = YES/" ${DOCS_CONFIG_FILE}
	sed -i "s|EXCLUDE                =|EXCLUDE                = ${DOCS_DIR} lib build_info|" ${DOCS_CONFIG_FILE}
	sed -i "s/RECURSIVE              = NO/RECURSIVE              = YES/" ${DOCS_CONFIG_FILE}
	 
}

display_warnings_generated() {
	# Echo the function's function
	print_color ""
	print_color ">>>> Display Any/All Warnings/Errors Generated by doxygen..." "BLUE"

	# Read the Warnings
	WARNINGS_IN_LOGFILE=$( cat ${WARN_DOC} )
	
	# Output the warnings if there are any
	print_color ">>>> NOTE: All warnings/errors are stored in \"${WARN_DOC}\"" "BLUE"
	if [ -z "${WARNINGS_IN_LOGFILE}" ]; then 
		print_color ">>>> No Warnings Generated to Display" "GREEN"
	else
		print_color "---------------------------WARNINGS---------------------------" "YELLOW"
		print_color "${WARNINGS_IN_LOGFILE}"
		print_color "--------------------------------------------------------------" "YELLOW"
	fi
	
}


create_doxygen_documentation() {
	# Echo the function's function
	print_color ""
	print_color ">>>> Creating doxygen Documentation for Project..." "BLUE"

	# Generate the Documentation
	doxygen ${DOCS_CONFIG_FILE} ${DOCS_DIR}
	
	print_color ""
	print_color "-----------------ADDITIONAL-DOXYGEN-COMMANDS------------------" "YELLOW"
	print_color "Addtional commands to help documentation: " "YELLOW"
	print_color "To define a ToDo tasks, put \'\ todo\'(NO space) in a comment" "YELLOW"
	print_color "To define a test, put \'\ test\'(NO space) in a comment" "YELLOW"
	print_color "To define a bug, put \'\ bug\'(NO space) in a comment" "YELLOW"
	print_color "To define something as deprecated, put \"\deprecated\" in a comment" "YELLOW"
	print_color "--------------------------------------------------------------" "YELLOW"
}

finalise_documentation_generator() {
	# Echo the function's function
	print_color ""
	print_color ">>>> Verifying Generated Documentation" "BLUE"
	
	# Determine whether the necessary files exist
	printf "${BLUE}>> Verifying documentation directory :       ${NC}"
	if [ -d  ${DOCS_DIR} ] ; then
		print_color "[ DONE ]" "GREEN"
	else
		print_color "[ FAIL ]" "RED"
		DOCS_SUCCESSFUL="False"
	fi
	
	printf "${BLUE}>> Verifying doxygen configuration file :    ${NC}"
	if [ -e  ${DOCS_CONFIG_FILE} ] ; then
		print_color "[ DONE ]" "GREEN"
	else
		print_color "[ FAIL ]" "RED"
		DOCS_SUCCESSFUL="False"
	fi
	
	printf "${BLUE}>> Verifying doxygen warning log file :      ${NC}"
	if [ -e  ${WARN_DOC} ] ; then
		print_color "[ DONE ]" "GREEN"
	else
		print_color "[ FAIL ]" "RED"
		DOCS_SUCCESSFUL="False"
	fi
	
	printf "${BLUE}>> Verifying doxygen generated HTML doc :    ${NC}"
	if [ -e  "${DOCS_DIR}/html/index.html" ] ; then
		print_color "[ DONE ]" "GREEN"
	else
		print_color "[ FAIL ]" "RED"
		DOCS_SUCCESSFUL="False"
	fi
	
	printf "${BLUE}>> Verifying doxygen generated LaTeX doc :   ${NC}"
	if [ -e  "${DOCS_DIR}/latex/Makefile" ] ; then
		print_color "[ DONE ]" "GREEN"
	else
		print_color "[ FAIL ]" "RED"
		DOCS_SUCCESSFUL="False"
	fi
	
	printf "${BLUE}>> Verifying doxygen generated xml doc :     ${NC}"
	if [ -e  "${DOCS_DIR}/xml/index.xml" ] ; then
		print_color "[ DONE ]" "GREEN"
	else
		print_color "[ FAIL ]" "RED"
		DOCS_SUCCESSFUL="False"
	fi
	
	printf "${BLUE}>> Verifying doxygen generated docbook doc : ${NC}"
	if [ -e  "${DOCS_DIR}/docbook/index.xml" ] ; then
		print_color "[ DONE ]" "GREEN"
	else
		print_color "[ FAIL ]" "RED"
		DOCS_SUCCESSFUL="False"
	fi
	
	print_color ""
	print_color "--------------------------------------------------------------" "BLUE"
	
	if [ ${DOCS_SUCCESSFUL} == "True" ] ; then
		print_color ">>>> RESULT: ALL DOCS GENERATED" "GREEN"
	else
		print_color ">>>> RESULT: ERROR GENERATING DOCS" "RED" 
	fi
	
	print_color "--------------------------------------------------------------" "BLUE"
	print_color ""
}

##------------------------------------------------------------------------------------------
## SECTION: Program Logic
##------------------------------------------------------------------------------------------
# Make sure doxygen is installed program is installed
install_doxygen

# Run doxygen automatically with the pre-determined settings, editing the files as necessary
configure_doxygen

# Create the documentation
create_doxygen_documentation
display_warnings_generated

# Finished program execution
finalise_documentation_generator

