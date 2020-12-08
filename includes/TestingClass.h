
#pragma once

/** @brief Dummy class used for illustration purposes. Doing something with it.

    Detailed description follows here.
    For more examples of doxygen comments, look here [https://www.doxygen.nl/manual/docblocks.html] and
    [https://flcwiki.desy.de/How%20to%20document%20your%20code%20using%20doxygen]
    
    @author X. XYZ, DESY
    @date March 2008

*/


class TestingClass {

	public:
		/** Default Constructor. Does something
		@param input the value to store
		*/
		TestingClass(int input = 0);
		/** Default Destructor. Does something
		*/
		~TestingClass();

		/** Returns the value stored as a private member
		@return the actual value stored
		*/
		int get_value();

	private:
		int m_stored_value; /**<stored value>*/

};
