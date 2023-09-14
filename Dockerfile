FROM silkeh/clang

RUN apt-get update && apt-get install -y \
  valgrind \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY src/ /workspace/src/
COPY test/ /workspace/test/
COPY .clang-format /workspace/.clang-format
COPY .editorconfig /workspace/.editorconfig
COPY CHANGELOG.md /workspace/CHANGELOG.md
COPY LICENSE.txt /workspace/LICENSE.txt
COPY Makefile /workspace/Makefile
COPY README.md /workspace/README.md

CMD [ "make", "testmem" ]
