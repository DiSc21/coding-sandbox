FROM jenkins/jenkins:2.375.1
USER root

RUN apt-get update && apt-get install -y lsb-release
RUN curl -fsSLo /usr/share/keyrings/docker-archive-keyring.asc https://download.docker.com/linux/debian/gpg

RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.asc] \
  https://download.docker.com/linux/debian $(lsb_release -cs) stable" > /etc/apt/sources.list.d/docker.list

RUN apt-get update && apt-get install -y --fix-missing build-essential
RUN apt-get update && apt-get install -y --fix-missing docker-ce-cli

RUN echo "jenkins ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
RUN echo "jarjar ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN groupadd -g 971 docker \
    && usermod -a -G docker jenkins

USER jenkins

# who doesn't like drunk swimming in the ocean to see the stages in a different light?
RUN jenkins-plugin-cli --plugins "blueocean:1.26.0 docker-workflow:563.vd5d2e5c4007f"
#RUN jenkins-plugin-cli --plugins junit:1166.va_436e268e972

# as the name might suggest, some pluging for code-coverage
RUN jenkins-plugin-cli --plugins code-coverage-api:3.4.1

# basically managing all the code-quality stuff, e.g. static code analysis and gcc/clang warnings
RUN jenkins-plugin-cli --plugins warnings-ng:9.22.0

# e.g. for gcovr generated coverage html
RUN jenkins-plugin-cli --plugins htmlpublisher:1.31

# just for a dirky dark look
RUN jenkins-plugin-cli --plugins dark-theme:262.v0202a_4c8fb_6a

CMD mkdir /ws/
WORKDIR /ws/

CMD ["Jenkins up and running!"]
