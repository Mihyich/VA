CCPP := g++

INC := .\inc
SRC := .\src
OUT := .\out
OUT_R := $(OUT)\Release
OUT_D := $(OUT)\Debug

# Flags
CFAGS := -std=c99 -Wall -Wextra -Wpedantic -I$(INC) -DUNICODE -D_UNICODE
CPPFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -I$(INC) -DUNICODE -D_UNICODE

# условная сборка
mode := release

ifeq ($(mode), release)
	CFAGS += -DNDEBUG -g0 -o3
	CPPFLAGS += -DNDEBUG -g0 -o3
	OUT := $(OUT_R)
endif

ifeq ($(mode), debug)
	CFAGS += -D_DEBUG -g3
	CPPFLAGS += -D_DEBUG -g3
	OUT := $(OUT_D)
endif

# файлы приложения
APP_OBJ := $(OUT)/main.o $(OUT)/ER_POL.o $(OUT)/LE.o

app.exe : $(APP_OBJ)
	$(CCPP) -o $@ $^

$(APP_OBJ) : $(OUT)/%.o : $(SRC)/%.cpp | $(OUT)
	$(CCPP) $(CPPFLAGS) -c $< -o $@

$(OUT):
	@if not exist "$(OUT)" mkdir "$(OUT)"

.PHONY: clean
clean:
	@if exist "$(OUT)" rd /s /q $(OUT)
	@if exist ".\*.exe" del /q .\*.exe
	@if exist ".\*dll" del /q .\*dll
	@if exist ".\*lib" del /q .\*lib
