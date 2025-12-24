# S3SpeakAssistant – AI contributor guide

## What’s here right now
- Repository snapshot: only `board.url` (AliExpress product link) and board images `board1.png` / `board2.png` / `board3.png`. No source code, build scripts, or documentation yet.
- Treat existing image assets as intentional references; do not delete or overwrite without explicit approval.

## Working assumptions
- Architecture, stack, and requirements are not present in the repo. Before adding code, confirm the target platform, language, and scope with the maintainer.
- There are no build/test commands or package manifests available. Introduce them explicitly when you add the first code.

## How to add code safely
- Start by proposing a minimal project scaffold (language + tooling) based on maintainer guidance; keep initial PRs small and reviewable.
- When adding new assets, keep filenames clear and predictable; avoid renaming the existing board images.
- Document any new conventions (linting, formatting, testing, deployment) in the README and update this file once the stack is known.

## Open questions to clarify with the maintainer
- What is the intended product? (Web app, mobile app, firmware, data pipeline, etc.)
- Preferred language/runtime and frameworks? (e.g., Node/React, Python/FastAPI, C#/.NET, etc.)
- Target AWS services or S3 usage patterns implied by the project name?
- Expected deliverables for a first milestone (UI mock, API, prototype) and any performance/security constraints?

## Next steps for AI agents
- Ask for the missing architectural and workflow details before committing substantial code.
- Once scope is defined, add a README with setup/run/test instructions and expand this document with project-specific patterns.
