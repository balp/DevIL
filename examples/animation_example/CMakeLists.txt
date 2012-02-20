
SET( Example_Animation_SRCS AnimTest.cpp AnimTest.rc )
SOURCE_GROUP(code FILES ${Example_Animation_SRCS} )
ADD_EXECUTABLE(Example_Animation ${Example_Animation_SRCS})
TARGET_LINK_LIBRARIES(Example_Animation
	IL
	ILU
	ILUT
)

