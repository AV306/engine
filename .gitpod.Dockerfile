FROM gitpod/workspace-full-vnc

SHELL ["/bin/bash", "-c"]
RUN sudo apt install libsfml-dev -y
RUN wget https://github.com/TheMilkies/Cate/releases/download/v2.9.6/cate_2.9-6_amd64.deb
RUN sudo dpkg -i cate_2.9-6_amd64.deb
RUN rm cate_2.9-6_amd64.deb
RUN source /etc/lsb-release
