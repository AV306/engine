FROM gitpod/workspace-full-vnc

SHELL ["/bin/bash", "-c"]
RUN sudo apt install sfml-dev -y
RUN source /etc/lsb-release
