#!/bin/bash
#SBATCH --job-name=kmc
#SBATCH --mail-type=ALL
#SBATCH --mail-user=aysegul.bumin@ufl.edu
#SBATCH --qos=boucher-b
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=10
#SBATCH --mem=50gb
#SBATCH --time=90:00:00
#SBATCH --output=kmc_%j.log
#SBATCH --array=0-19,56-99



date;hostname;pwd

echo -e "This is array task number ${SLURM_ARRAY_TASK_ID}"
run=${SLURM_ARRAY_TASK_ID}

module load kmc/3.1.0

rm -rf tmp${run}

mkdir tmp${run}

kmc -k31 NotContam${run}.R1.fastq out_1_${run} tmp${run}

kmc -k31 NotContam${run}.R2.fastq out_2_${run} tmp${run}

kmc_tools simple out_1_${run} out_2_${run} union merge${run}

kmc_dump merge${run} Kmer${run}.txt


date
