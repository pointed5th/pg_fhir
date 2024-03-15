EXTENSION = fhirx
DATA = $(EXTENSION)--1.0.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

all: $(DATA)

$(DATA): $(EXTENSION).o
    mkdir -p .tmp
    sed -e 's/MODULE_PATHNAME/$$libdir/g' \
        < $(EXTENSION).control > .tmp/$(EXTENSION).control
    $(PG_REGRESS) --dll=$(EXTENSION).so --create-extension=$(EXTENSION) \
        --set-output .tmp/$(EXTENSION)--1.0.sql

$(EXTENSION).o: $(EXTENSION).c
    $(CC) $(CFLAGS) -c $(EXTENSION).c

clean:
    rm -rf .tmp $(EXTENSION).o $(EXTENSION).so