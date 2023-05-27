NAME	:= wordle
LIB	:= ./lib/
OBJDIR	:= ./obj
SRCDIR	:= ./srcs/
SRC	:= main.cpp wordle.cpp board.cpp dictionary.cpp
ENTRY	:=

INCS	:= ./include
IFLAGS	:= $(addprefix -I,$(INCS))
SRCS	:= $(addprefix $(SRCDIR), $(SRC))
OBJS	:= $(SRCS:.cpp=.o)
OBJECTS	:= $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
DEPS	:= $(OBJECTS:.o=.d)
LDFLAGS :=  -lncurses

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++14

ifdef WITH_CHEAT
CXXFLAGS += -D CHEAT=1
endif

all:
	@make $(NAME)	

$(NAME)	:	$(OBJECTS)
		$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@mkdir -p $(OBJDIR) / $(*D)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -MMD -MP -MF $(OBJDIR)/$*.d  -o $@

$(OBJDIR) :
	@mkdir $(OBJDIR)

clean	:
			$(RM) -r $(OBJDIR)

fclean	:	clean
			$(RM) $(NAME)

re	:		fclean all

cheat 	: fclean
		make WITH_CHEAT=1

bonus	:	
			@make WITH_BONUS=1

run		:
	./${NAME} ./words.txt

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: all clean fclean bonus re cheat run

